program matsum
  implicit none

  ! Variable declarations
  integer :: a_rows, a_cols, b_rows, b_cols, c_rows, c_cols
  integer :: i
  integer :: a_io, b_io, c_io, fa_stat, fb_stat, fc_stat
  real*8, allocatable :: a(:), b(:), c(:)
  character *32 :: fa, fb, fc
  logical :: fa_exists, fb_exists, fc_exists

  ! Ask user for matrices filename
  print *, "Matrix A filename?"
  read  *, fa
  print *, "Matrix B filename?"
  read  *, fb
  print *, "Matrix C filename?"
  read  *, fc

  ! Check if files exist
  inquire(file = fa, exist = fa_exists)
  inquire(file = fb, exist = fb_exists)
  inquire(file = fc, exist = fc_exists)
  if (.not. fa_exists .or. .not. fb_exists) then
    print *, "error: matrix A or B does not exist"
    call exit
  end if

  ! Open files
  open(newunit = a_io, file = fa, action = "read", iostat = fa_stat)
  open(newunit = b_io, file = fb, action = "read", iostat = fb_stat)
  if (fc_exists) then
    open(newunit = c_io, file = fc, status = "replace", action = "write", iostat = fc_stat)
  else
    open(newunit = c_io, file = fc, status = "new", action = "write", iostat = fc_stat)
  end if

  ! Check if files opened correctly
  if (fa_stat /= 0 .or. fb_stat /= 0 .or. fc_stat /= 0) then
    print *, "error: failed to open one of the matrices files"
    call exit
  end if

  ! Read matrix A
  read(a_io, '(I1, X, I1)') a_rows, a_cols
  allocate(a(a_rows * a_cols))
  read(a_io, *) (a(i), i = 1, a_rows * a_cols)

  ! Read matrix B
  read(b_io, '(I1, X, I1)') b_rows, b_cols
  allocate(b(b_rows * b_cols))
  read(b_io, *) (b(i), i = 1, b_rows * b_cols)

  ! Check if matrices a_rowse summable
  if ((a_rows /= b_rows) .and. (a_cols /= b_cols)) then
    print *, "error: matrices cannot be summed (not same size)"
    call exit
  end if

  ! Initialize C matrix
  c_rows = a_rows
  c_cols = a_cols
  allocate(c(c_rows * c_cols))

  ! Compute sum
  c = a + b

  ! Write values to file
  write(c_io, '(I1, X, I1)') c_rows, c_cols
  do i = 1, c_rows * c_cols
    print *, c(i)
    write(c_io, '(F17.15, X)', advance = 'no') c(i)
  end do

  ! Close files
  close(a_io)
  close(b_io)
  close(c_io)

  ! Deallocate arrays
  deallocate(a)
  deallocate(b)
  deallocate(c)
end program matsum
