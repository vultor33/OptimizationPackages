       SUBROUTINE FUNCT(N,X,FX)
       INTEGER N
       DOUBLE PRECISION X(N), FX
       LOGICAL file_exists



       FX = X(1) * X(1) - 1


       ! WRITE ALL POINTS AT RESTART FILE
        OPEN(UNIT=40,FILE='restart.simp',STATUS='old',ACCESS = 'append')
        WRITE(40,*) FX
        DO i=1,N
           WRITE(40,*) X(i)
        ENDDO
        CLOSE(40)
        ! WROTE

       RETURN
       END
