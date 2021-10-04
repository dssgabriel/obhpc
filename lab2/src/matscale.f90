program matreduc
  implicit none

  ! Variable declarations
  integer :: rows, cols, factor
  integer :: i
  integer :: io, stat
  real *8, allocatable :: m(:)
  character *32 :: filename
  logical :: exists

  ! Ask user for matrix filename
  print "(a16)", "Matrix filename?"
  read *, filename
  filename = trim(filename)
  print "(a13)", "Scale factor?"
  read *, factor

  ! Check if file exists
  inquire(file = filename, exist = exists)
  if (.not. exists) then
    print "(a28)", "error: matrix does not exist"
    call exit
  end if

  ! Open file for reading
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
  close(io)

  ! Scale matrix
  do i = 1, rows * cols
    m(i) = m(i) * factor
  end do

  ! Open file for writing
  open(newunit = io, file = filename, action = "write", status = "replace", iostat = stat)
  ! Check if file opened correctly
  if (stat /= 0) then
    print "(a47)", "error: failed to open matrix file"
    call exit
  end if

  ! Write results to file
  write(io, '(i1, x, i1)') rows, cols
  do i = 1, rows * cols
    write(io, '(f17.15, x)', advance = 'no') m(i)
  end do

  ! Close file and deallocate matrix
  close(io)
  deallocate(m)
end program matreduc
