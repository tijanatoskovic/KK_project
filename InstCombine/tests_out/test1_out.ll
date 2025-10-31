; ModuleID = 'tests/test1.ll'
source_filename = "tests/test1.ll"

define i32 @test_swap_operands(i32 %x) {
  %add = add i32 %x, 5
  ret i32 %add
}
