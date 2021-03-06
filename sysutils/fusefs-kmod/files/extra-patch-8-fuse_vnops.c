--- fs/fuse/fuse_vnops.c.orig
+++ fs/fuse/fuse_vnops.c
@@ -190,10 +190,10 @@
 
 int	fuse_pbuf_freecnt = -1;
 
-#define fuse_vm_page_lock(m)		vm_page_lock((m));
-#define fuse_vm_page_unlock(m)		vm_page_unlock((m));
-#define fuse_vm_page_lock_queues()	((void)0)
-#define fuse_vm_page_unlock_queues()	((void)0)
+#define fuse_vm_page_lock(m)		((void)0)
+#define fuse_vm_page_unlock(m)		((void)0)
+#define fuse_vm_page_lock_queues()	vm_page_lock_queues()
+#define fuse_vm_page_unlock_queues()	vm_page_unlock_queues()
 
 /*
     struct vnop_access_args {
@@ -579,7 +579,7 @@
 	}
 
 	if ((fvdat->flag & FN_REVOKED) != 0 && fuse_reclaim_revoked) {
-		vrecycle(vp);
+		vrecycle(vp, curthread);
 	}
 	return 0;
 }
@@ -706,7 +706,7 @@
 		op = FUSE_GETATTR;
 		goto calldaemon;
 	} else if (fuse_lookup_cache_enable) {
-		err = cache_lookup(dvp, vpp, cnp, NULL, NULL);
+		err = cache_lookup(dvp, vpp, cnp);
 		switch (err) {
 
 		case -1:		/* positive match */
@@ -1758,7 +1758,7 @@
 	 * can only occur at the file EOF.
 	 */
 
-	VM_OBJECT_WLOCK(vp->v_object);
+	VM_OBJECT_LOCK(vp->v_object);
 	fuse_vm_page_lock_queues();
 	if (pages[ap->a_reqpage]->valid != 0) {
 		for (i = 0; i < npages; ++i) {
@@ -1769,11 +1769,11 @@
 			}
 		}
 		fuse_vm_page_unlock_queues();
-		VM_OBJECT_WUNLOCK(vp->v_object);
+		VM_OBJECT_UNLOCK(vp->v_object);
 		return 0;
 	}
 	fuse_vm_page_unlock_queues();
-	VM_OBJECT_WUNLOCK(vp->v_object);
+	VM_OBJECT_UNLOCK(vp->v_object);
 
 	/*
 	 * We use only the kva address for the buffer, but this is extremely
@@ -1803,7 +1803,7 @@
 
 	if (error && (uio.uio_resid == count)) {
 		FS_DEBUG("error %d\n", error);
-		VM_OBJECT_WLOCK(vp->v_object);
+		VM_OBJECT_LOCK(vp->v_object);
 		fuse_vm_page_lock_queues();
 		for (i = 0; i < npages; ++i) {
 			if (i != ap->a_reqpage) {
@@ -1813,7 +1813,7 @@
 			}
 		}
 		fuse_vm_page_unlock_queues();
-		VM_OBJECT_WUNLOCK(vp->v_object);
+		VM_OBJECT_UNLOCK(vp->v_object);
 		return VM_PAGER_ERROR;
 	}
 	/*
@@ -1823,7 +1823,7 @@
 	 */
 
 	size = count - uio.uio_resid;
-	VM_OBJECT_WLOCK(vp->v_object);
+	VM_OBJECT_LOCK(vp->v_object);
 	fuse_vm_page_lock_queues();
 	for (i = 0, toff = 0; i < npages; i++, toff = nextoff) {
 		vm_page_t m;
@@ -1843,7 +1843,7 @@
 			 * Read operation filled a partial page.
 			 */
 			m->valid = 0;
-			vm_page_set_valid_range(m, 0, size - toff);
+			vm_page_set_valid(m, 0, size - toff);
 			KASSERT(m->dirty == 0,
 			    ("fuse_getpages: page %p is dirty", m));
 		} else {
@@ -1854,11 +1854,36 @@
 			 */
 			;
 		}
-		if (i != ap->a_reqpage)
-			vm_page_readahead_finish(m);
+		if (i != ap->a_reqpage) {
+			/*
+			 * whether or not to leave the page activated is up in
+			 * the air, but we should put the page on a page queue
+			 * somewhere. (it already is in the object). Result:
+			 * It appears that empirical results show that
+			 * deactivating pages is best.
+			 */
+
+			/*
+			 * just in case someone was asking for this page we
+			 * now tell them that it is ok to use
+			 */
+			if (!error) {
+#ifdef VPO_WANTED
+				if (m->oflags & VPO_WANTED)
+#else
+				if (m->flags & PG_WANTED)
+#endif
+					vm_page_activate(m);
+				else
+					vm_page_deactivate(m);
+				vm_page_wakeup(m);
+			} else {
+				vm_page_free(m);
+			}
+		}
 	}
 	fuse_vm_page_unlock_queues();
-	VM_OBJECT_WUNLOCK(vp->v_object);
+	VM_OBJECT_UNLOCK(vp->v_object);
 	return 0;
 }
 
@@ -1947,9 +1972,9 @@
 
 		for (i = 0; i < nwritten; i++) {
 			rtvals[i] = VM_PAGER_OK;
-			VM_OBJECT_WLOCK(pages[i]->object);
+			VM_OBJECT_LOCK(pages[i]->object);
 			vm_page_undirty(pages[i]);
-			VM_OBJECT_WUNLOCK(pages[i]->object);
+			VM_OBJECT_UNLOCK(pages[i]->object);
 		}
 	}
 	return rtvals[0];
