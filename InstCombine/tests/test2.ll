define i32 @test_add_chain(i32 %x) {
  %add1 = add i32 %x, 1
  %add2 = add i32 %add1, 2
  ret i32 %add2
}
