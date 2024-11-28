
# Design Decision: Refactoring PushFont to Accept an Index

This document explains the rationale behind refactoring the `PushFont` function to accept an integer index instead of a pointer, as implemented in the project.

## Key Advantages of the Refactor

1. **Simplifies JavaScript API**  
   By requiring an index instead of a pointer, the JavaScript side remains simple and intuitive. Developers don't need to deal with raw pointers or `BigInt`, which can be error-prone or lead to runtime issues like segmentation faults.

2. **Improved Safety**  
   Passing an integer index is much safer compared to dealing with raw memory pointers. This avoids the risk of invalid memory access, null pointers, or corrupted memory issues.

3. **Better Encapsulation**  
   The responsibility of managing and accessing font pointers stays in the C++ layer, where it belongs. The JavaScript layer only needs to know about indices, which is a more abstract and user-friendly representation.

4. **Error Handling**  
   The refactor makes it easy to validate the index range on the C++ side, providing better error messages if someone tries to access a font that doesn't exist. This makes the API more robust.

5. **Alignment with ImGui’s Design**  
   ImGui already works heavily with indices for things like table columns or style variables. This design aligns well with ImGui's existing conventions.

6. **Flexibility for Future Changes**  
   If the internal font management changes in ImGui (e.g., fonts being stored differently), this approach is more adaptable because the JS side won’t need to be updated—it only cares about indices.

---

## Conclusion

This refactor improves the API's usability, safety, and maintainability while aligning with the existing conventions of ImGui. By delegating low-level pointer management to the C++ layer, the JavaScript interface becomes more user-friendly and robust.
