define i32 @test2(i32* %p) {
entry:
    %a = load i32, i32* %p
    %b = mul i32 %a, 2    ; mrtva instrukcija
    %c = add i32 %a, 3
    ret i32 %c
}
