module matrix_ops
  implicit none

  private
  public :: mat_print, mat_sum, mat_mul, mat_reduc, mat_scale

  type, public :: matrix_t(rows, cols)
    integer, len, public :: rows
    integer, len, public :: cols
    real *8, dimension(rows * cols) :: values
  end type
contains
  ! Helper subroutine to print a matrix
  subroutine mat_print(M)
    type(matrix_t(rows = 0, cols = 0)), intent(in) :: M

    integer :: i

    do i = 1, size(M%values)
      print "(f17.15)", M%values(i)
    end do
  end subroutine mat_print

  ! Matrix sum
  subroutine mat_sum(A, B, C)
    type(matrix_t(rows = 0, cols = 0)), intent(in) :: A, B
    type(matrix_t(A%rows, A%cols)), intent(out) :: C

    ! Check that matrices are the same size
    if (A%rows /= B%rows .or. A%cols /= B%cols) then
      print "(a45)", "error: cannot sum matrices (not same size)"
      call exit
    end if

    ! Compute sum
    C%values = A%values + B%values
  end subroutine mat_sum

  ! Matrix multiplication
  subroutine mat_mul(A, B, C)
    type(matrix_t(rows = 0, cols = 0)), intent(in) :: A, B
    type(matrix_t(A%rows, A%cols)), intent(out) :: C
    integer :: i, j, k
    real *8 :: loc

    ! Check that multilication is possible
    if (A%rows /= B%cols) then
      print "(a50)", "error: cannot multiply matrices (A.rows /= B.cols)"
      call exit
    end if

    ! Compute product
    do i = 0, A%rows - 1
      do j = 0, B%rows - 1
        loc = A%values(i * A%cols + j + 1)
        do k = 0, B%cols - 1
          C%values(i * C%cols + k + 1) = C%values(i * C%cols + k + 1) + loc * B%values(j * B%cols + k + 1)
        end do
      end do
    end do
  end subroutine mat_mul

  ! Matrix reduction
  subroutine mat_reduc(M, redux)
    type(matrix_t(rows = 0, cols = 0)), intent(in) :: M
    real *8, intent(out) :: redux

    integer :: i

    do i = 1, size(M%values)
      redux = redux + M%values(i)
    end do
  end subroutine mat_reduc

  ! Matrix scale
  subroutine mat_scale(A, B, factor)
    type(matrix_t(rows = 0, cols = 0)), intent(in) :: A
    integer, intent(in) :: factor
    type(matrix_t(A%rows, A%cols)), intent(out) :: B

    integer :: i

    do i = 1, size(A%values)
      B%values(i) = A%values(i) * factor
    end do
  end subroutine mat_scale
end module matrix_ops
