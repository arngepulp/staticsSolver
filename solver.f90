! get values from csv files form of
! point, vector from orgin
! fx,fy,d_point,theta,N,d_point,slopetriangle,N,d_point or other forms
! d_point will be converted to distance from orgin upon entry into C++ OOP GUI plan
! some forms will be 0 so can convert into fx fy and then add, remove all collumns except for first 2 to get 0
! make systems of eqns to solve
! brute force solve system
! display results
program solver
    implicit none
    !read vals from csv
    real, allocatable :: forceArray(:,:);
    integer :: forceID, numLinesID, geometryID, i, j, numForces, numPoints
    character(len=256) :: line
    character(len=20) :: value
    logical :: read_success

    ! open file and find how many lines
    numLinesID = 11 
    open(numLinesID, file = 'numLines.txt', status='old', action='read')
    read(numLinesID,'(A)') line
    read(line,*) numForces
    read(numLinesID,'(A)') line
    read(line,*) numPoints
    close(numLinesID)
    allocate(forceArray(numForces,4))
    ! testing
    print*, numForces," ", numPoints

    ! Open forces.csv File
    forceID = 10 ! file ID basically
    open(forceID, file ='forces.csv', status='old', action='read')


    ! Read forces.csv
    ! Read forces.csv
    i = 1
    read(forceID, '(A)') line
    do while (i <= numForces)
        read(forceID, '(A)') line
        if (len_trim(line) == 0) exit ! Exit loop if line is empty

        ! Comma delimiting
        j = 1
        do while (len_trim(line) > 0) ! While length of line is greater than 0
            call get_value(line, value)
            value = trim(value)  ! Trim any spaces from the value


            ! Attempt to read into forceArray
            read(value, *) forceArray(i, j)
            j = j + 1
            if (j > 4) exit ! Exit if more than 4 columns are read
        end do
        i = i + 1
    end do

    ! testing if file was read properly
    
    ! solve somehow numerical methods and stuff probably set unknowns as idk how to deal with those but x system of equation solving
    ! unknown will be values numLine.txt 3rd line
endprogram solver

subroutine get_value(line, value)
    character(len=*), intent(inout) :: line
    character(len=*), intent(out) :: value
    integer :: comma_pos

    ! Find position of the first comma
    comma_pos = index(line, ',')

    if (comma_pos > 0) then
        ! Extract the value and remove it from the line
        value = line(1:comma_pos-1)
        line = line(comma_pos+1:)
    else
        ! If no comma, return the entire line as the value and clear the line
        value = line
        line = ''
    end if
end subroutine get_value