; ModuleID = 'tests/test3.ll'
source_filename = "tests/test3.ll"

define i32 @test_mul_shift(i32 %x) {
  %1 = shl i32 %x, 1
  ret i32 %1
}
