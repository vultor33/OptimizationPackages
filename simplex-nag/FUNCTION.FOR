       SUBROUTINE FUNCT(N,X,FX)
       INTEGER N, KALLFIT, KACTUALFIT
       DOUBLE PRECISION X(N), FX
       DOUBLE PRECISION ALLFITNESS(10000000)
       LOGICAL file_exists
       COMMON  ALLFITNESS, KALLFIT, KACTUALFIT

        KACTUAL = KACTUAL + 1
        if(KACTUAL .lt. KALLFIT) then
                FX = ALLFITNESS(KACTUAL)
                RETURN
        endif


        call system("rm point.txt")
        open(unit=13,file='point.txt',status='new')
        write(13,*) N
        do j=1,N
                write(13,*) X(j)
        enddo
        close(13)

        call system("./getFitness.x")

        open(unit=14,file='fitness.txt',status='old')
        read(14,*) FX
        close(14)

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
