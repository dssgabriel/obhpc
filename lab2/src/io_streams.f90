module io_streams
  use matrix_ops, only: matrix_t
  implicit none

  private
  public :: mat_write, mat_read
contains
  subroutine mat_write(fname, fp, M)
    character *32, intent(in) :: fname
    type(matrix_t(rows = 0, cols = 0)), intent(in) :: M
    integer, intent(out) :: fp

    character *256 :: fmsg
    integer :: fstat, i
    logical :: fexist

    ! Check if file exists
    inquire(file = fname, exist = fexist)
    if (.not. fexist) then
      open(newunit = fp, file = fname, status = "new", action = "write", iostat = fstat, iomsg = fmsg)
    else
      open(newunit = fp, file = fname, status = "replace", action = "write", iostat = fstat, iomsg = fmsg)
    end if

    ! Check that file opened correctly
    if (fstat /= 0) then
      print *, fmsg
      call exit
    end if

    ! Write matrix to file
    write(fp, '(i1, x, i1)') M%rows, M%cols
    do i = 1, size(M%values)
      write(fp, '(f17.15, x)', advance = 'no') M%values(i)
    end do
  end subroutine mat_write

  subroutine mat_read()
  end subroutine mat_read
end module io_streams
