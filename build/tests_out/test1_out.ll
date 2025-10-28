; ModuleID = '/home/toto/Desktop/kk_project/KK_project/tests/test1_out.ll'
source_filename = "tests/test1.ll"

define i32 @test1(i32 %x) {
entry:
  %y = add i32 %x, 2
  ret i32 %y
}
