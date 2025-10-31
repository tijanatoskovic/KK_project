; ModuleID = 'tests/test1.ll'
source_filename = "tests/test1.ll"

define i32 @test1(i32 %x) {
entry:
  %y = add i32 %x, 2
  ret i32 %y
}
