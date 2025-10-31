; ModuleID = 'tests/test3.ll'
source_filename = "tests/test3.ll"

define i32 @test3(i32 %x) {
entry:
  %a = add i32 %x, 1
  ret i32 %a
}
