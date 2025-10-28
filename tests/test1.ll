; funkcija ima mrtvu instrukciju
define i32 @test1(i32 %x) {
entry:
    %dead = add i32 %x, 1
    %y = add i32 %x, 2
    ret i32 %y
}