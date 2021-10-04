program genmat
  implicit none

  ! Variable declarations
  integer :: rows, cols, length, i, io, stat
  real*8, allocatable :: m(:)
  real*8 :: rand
  character *32 :: filename
  logical :: exists

  ! Ask user for matrix dimensions and filename
  print *, "Number of rows:"
  read  *, rows
  print *, "Number of cols:"
  read  *, cols
  print *, "Filename:"
  read  *, filename

  ! Compute length of the matrix array
  length = rows * cols

  ! Allocate memory for the matrix
  allocate(m(length))

  ! Fill array with random values
  do i = 1, length
    call random_number(rand)
    m(i) = rand
  end do

  ! Check if file exists
  inquire(file = filename, exist = exists)
  if (exists) then
    open(newunit = io, file = filename, status = "replace", action = "write", iostat = stat)
  else
    open(newunit = io, file = filename, status = "new", action = "write", iostat = stat)
  end if

  ! Write values to file
  if (stat == 0) then
    write(io, '(I1, X, I1)') rows, cols
    do i = 1, length
      write(io, '(F17.15, X)', advance = 'no') m(i)
    end do
  else
    call exit
  end if

  ! Close file and deallocate matrix
  close(io)
  deallocate(m)
end program genmat
