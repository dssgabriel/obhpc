program matreduc
  implicit none

  ! Variable declarations
  integer :: rows, cols
  integer :: i
  integer :: io, stat
  real *8, allocatable :: m(:)
  real *8 :: reduction = 0.0
  character *32 :: filename
  logical :: exists

  ! Ask user for matrix filename
  print "(a16)", "Matrix filename?"
  read *, filename
  filename = trim(filename)

  ! Check if file exists
  inquire(file = filename, exist = exists)
  if (.not. exists) then
    print "(a28)", "error: matrix does not exist"
    call exit
  end if

  ! Open file
  open(newunit = io, file = filename, action = "read", iostat = stat)

  ! Check if file opened correctly
  if (stat /= 0) then
    print "(a47)", "error: failed to open matrix file"
    call exit
  end if

  ! Read matrix A
  read(io, '(i1, x, i1)') rows, cols
  allocate(m(rows * cols))
  read(io, *) (m(i), i = 1, rows * cols)

  ! Accumulate matrix values into reduction variable
  do i = 1, rows * cols
    reduction = reduction + m(i)
  end do

  ! Print reduction
  print "(a12, f17.15)", "Reduction = ", reduction

  ! Close file and deallocate matrix
  close(io)
  deallocate(m)
end program matreduc
