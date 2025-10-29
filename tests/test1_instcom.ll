define i32 @test_swap_operands(i32 %x) {
  %add = add i32 5, %x
  ret i32 %add
}
