; ModuleID = 'tests/test2.ll'
source_filename = "tests/test2.ll"

define i32 @test2(i32* %p) {
entry:
  %a = load i32, i32* %p, align 4
  %c = add i32 %a, 3
  ret i32 %c
}
