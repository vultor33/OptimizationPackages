#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "global.h"
#include "rand.h"

void input ()
{
    int i;
    printf("\n Enter the problem relevant and algorithm relevant parameters ... ");
    printf("\n Enter the population size (a multiple of 4) : ");
    scanf("%d",&popsize);
    if (popsize<4 || (popsize%4)!= 0)
    {
        printf("\n population size read is : %d",popsize);
        printf("\n Wrong population size entered, hence exiting \n");
        exit (1);
    }
    printf("\n Enter the number of generations : ");
    scanf("%d",&ngen);
    if (ngen<1)
    {
        printf("\n number of generations read is : %d",ngen);
        printf("\n Wrong nuber of generations entered, hence exiting \n");
        exit (1);
    }
    printf("\n Enter the number of objectives : ");
    scanf("%d",&nobj);
    if (nobj<1)
    {
        printf("\n number of objectives entered is : %d",nobj);
        printf("\n Wrong number of objectives entered, hence exiting \n");
        exit (1);
    }
    min_obj = (double *)malloc(nobj*sizeof(double));
    max_obj = (double *)malloc(nobj*sizeof(double));
    epsilon = (double *)malloc(nobj*sizeof(double));
    printf("\n Enter the number of constraints : ");
    scanf("%d",&ncon);
    if (ncon<0)
    {
        printf("\n number of constraints entered is : %d",ncon);
        printf("\n Wrong number of constraints enetered, hence exiting \n");
        exit (1);
    }
    printf("\n Enter the number of real variables : ");
    scanf("%d",&nreal);
    if (nreal<0)
    {
        printf("\n number of real variables entered is : %d",nreal);
        printf("\n Wrong number of variables entered, hence exiting \n");
        exit (1);
    }
    if (nreal != 0)
    {
        min_realvar = (double *)malloc(nreal*sizeof(double));
        max_realvar = (double *)malloc(nreal*sizeof(double));
        for (i=0; i<nreal; i++)
        {
            printf ("\n Enter the lower limit of real variable %d : ",i+1);
            scanf ("%lf",&min_realvar[i]);
            printf ("\n Enter the upper limit of real variable %d : ",i+1);
            scanf ("%lf",&max_realvar[i]);
            if (max_realvar[i] <= min_realvar[i])
            {
                printf("\n Wrong limits entered for the min and max bounds of real variable, hence exiting \n");
                exit(1);
            }
        }
        printf ("\n Enter the probability of crossover of real variable (0.6-1.0) : ");
        scanf ("%lf",&pcross_real);
        if (pcross_real<0.0 || pcross_real>1.0)
        {
            printf("\n Probability of crossover entered is : %e",pcross_real);
            printf("\n Entered value of probability of crossover of real variables is out of bounds, hence exiting \n");
            exit (1);
        }
        printf ("\n Enter the probablity of mutation of real variables (1/nreal) : ");
        scanf ("%lf",&pmut_real);
        if (pmut_real<0.0 || pmut_real>1.0)
        {
            printf("\n Probability of mutation entered is : %e",pmut_real);
            printf("\n Entered value of probability of mutation of real variables is out of bounds, hence exiting \n");
            exit (1);
        }
        printf ("\n Enter the value of distribution index for crossover (5-20): ");
        scanf ("%lf",&eta_c);
        if (eta_c<=0)
        {
            printf("\n The value entered is : %e",eta_c);
            printf("\n Wrong value of distribution index for crossover entered, hence exiting \n");
            exit (1);
        }
        printf ("\n Enter the value of distribution index for mutation (5-50): ");
        scanf ("%lf",&eta_m);
        if (eta_m<=0)
        {
            printf("\n The value entered is : %e",eta_m);
            printf("\n Wrong value of distribution index for mutation entered, hence exiting \n");
            exit (1);
        }
    }
    printf("\n Enter the number of binary variables : ");
    scanf("%d",&nbin);
    if (nbin<0)
    {
        printf ("\n number of binary variables entered is : %d",nbin);
        printf ("\n Wrong number of binary variables entered, hence exiting \n");
        exit(1);
    }
    if (nbin != 0)
    {
        nbits = (int *)malloc(nbin*sizeof(int));
        min_binvar = (double *)malloc(nbin*sizeof(double));
        max_binvar = (double *)malloc(nbin*sizeof(double));
        for (i=0; i<nbin; i++)
        {
            printf ("\n Enter the number of bits for binary variable %d : ",i+1);
            scanf ("%d",&nbits[i]);
            if (nbits[i] < 1)
            {
                printf("\n Wrong number of bits for binary variable entered, hence exiting");
                exit(1);
            }
            printf ("\n Enter the lower limit of binary variable %d : ",i+1);
            scanf ("%lf",&min_binvar[i]);
            printf ("\n Enter the upper limit of binary variable %d : ",i+1);
            scanf ("%lf",&max_binvar[i]);
            if (max_binvar[i] <= min_binvar[i])
            {
                printf("\n Wrong limits entered for the min and max bounds of binary variable entered, hence exiting \n");
                exit(1);
            }
        }
        printf ("\n Enter the probability of crossover of binary variable (0.6-1.0): ");
        scanf ("%lf",&pcross_bin);
        if (pcross_bin<0.0 || pcross_bin>1.0)
        {
            printf("\n Probability of crossover entered is : %e",pcross_bin);
            printf("\n Entered value of probability of crossover of binary variables is out of bounds, hence exiting \n");
            exit (1);
        }
        printf ("\n Enter the probability of mutation of binary variables (1/nbits): ");
        scanf ("%lf",&pmut_bin);
        if (pmut_bin<0.0 || pmut_bin>1.0)
        {
            printf("\n Probability of mutation entered is : %e",pmut_bin);
            printf("\n Entered value of probability  of mutation of binary variables is out of bounds, hence exiting \n");
            exit (1);
        }
    }
    if (nreal==0 && nbin==0)
    {
        printf("\n Number of real as well as binary variables, both are zero, hence exiting \n");
        exit(1);
    }
    printf("\n Enter the choice for selection restriction, 0 for normal selection, 1 for restricted selection : ");
    scanf("%d",&mate);
    if (mate!=0 && mate!=1)
    {
        printf("\n Selection restriction option read as : %d",mate);
        printf("\n Wrong choice entered for selection restriction, hence exiting \n");
        exit(1);
    }
    printf("\n Enter the value of delta (0.0 - 1.0) for loose domination : ");
    scanf("%lf",&delta);
    if (delta<0.0 || delta>1.0)
    {
        printf("\n Wrong value entered for delta for loose domination, the value read was : %e",delta);
        printf("\n Exiting \n");
        exit(1);
    }
    printf("\n Do you want to enable variable space niching, 0 for NO, 1 for YES : ");
    scanf("%d",&var_option);
    if (var_option!=0 && var_option!=1)
    {
        printf("\n The choice read for variable space niching is %d",var_option);
        printf("\n Wrong choice entered, hence exiting \n");
        exit(1);
    }
    printf("\n Do you want to enable objective space niching, 0 for NO, 1 for YES : ");
    scanf("%d",&obj_option);
    if (obj_option!=0 && obj_option!=1)
    {
        printf("\n The choice read for objective space niching is %d",obj_option);
        printf("\n Wrong choice entered, hence exiting \n");
        exit(1);
    }
    if (var_option==0 && obj_option==0)
    {
        printf("\n Both variable and objective space niching cannot be zero, exiting\n");
        exit(1);
    }
    printf("\n Enter the choice for population initialization, 0 for random, 1 for latin-hypercube based sampling, 2 for reading initial population from a file : ");
    scanf("%d",&input_type);
    if (input_type!=0 && input_type!=1 && input_type!=2)
    {
        printf("\n Wrong choice entered for population initialization, choice entered was %d",input_type);
        printf("\n Exiting \n");
        exit(1);
    }
    printf("\n Enter the frequency with which the population information (only the variables) is to be stored : ");
    scanf("%d",&frequency);
    if (frequency<1 || frequency>ngen)
    {
        printf("\n Wrong value of frequency entered, the value read is : %d",frequency);
        printf("\n It should be in the range (1 - pop_size), exiting \n");
        exit(1);
    }
    printf("\n Enter the simulation mode, 0 for Analysis mode, 1 for Turbo mode : ");
    scanf("%d",&run_mode);
    if (run_mode!=0 && run_mode!=1)
    {
        printf("\n Value read for simulation mode is : %d",run_mode);
        printf("\n Wrong value entered, hence exiting \n");
        exit(1);
    }
    if (run_mode==0)
    {
        if (nobj==1)
        {
            choice = 0;
            printf("\n There is only one objective, so enter the variable number of real variable for X axis display : ");
            scanf("%d",&var1);
            if (var1<1 || var1>nreal)
            {
                printf("\n Wrong value for variable index entered, the value entered is : %d",var1);
                exit(1);
            }
        }
        else
        {
            if (nobj==2)
            {
                choice = 1;
                printf("\n Enter the objective for X axis display : ");
                scanf("%d",&obj1);
                if (obj1<1 || obj1>nobj)
                {
                    printf("\n Wrong value of X objective entered, value entered was %d\n",obj1);
                    exit(1);
                }
                printf("\n Enter the objective for Y axis display : ");
                scanf("%d",&obj2);
                if (obj2<1 || obj2>nobj)
                {
                    printf("\n Wrong value of Y objective entered, value entered was %d\n",obj2);
                    exit(1);
                }
                obj3 = -1;
            }
            else
            {
                printf("\n #obj > 2, 2D display or a 3D display ?, enter 2 for 2D and 3 for 3D :");
                scanf("%d",&choice);
                if (choice!=2 && choice!=3)
                {
                    printf("\n Entered the wrong choice, hence exiting, choice entered was %d\n",choice);
                    exit(1);
                }
                if (choice==2)
                {
                    printf("\n Enter the objective for X axis display : ");
                    scanf("%d",&obj1);
                    if (obj1<1 || obj1>nobj)
                    {
                        printf("\n Wrong value of X objective entered, value entered was %d\n",obj1);
                        exit(1);
                    }
                    printf("\n Enter the objective for Y axis display : ");
                    scanf("%d",&obj2);
                    if (obj2<1 || obj2>nobj)
                    {
                        printf("\n Wrong value of Y objective entered, value entered was %d\n",obj2);
                        exit(1);
                    }
                    obj3 = -1;
                }
                else
                {
                    printf("\n Enter the objective for X axis display : ");
                    scanf("%d",&obj1);
                    if (obj1<1 || obj1>nobj)
                    {
                        printf("\n Wrong value of X objective entered, value entered was %d\n",obj1);
                        exit(1);
                    }
                    printf("\n Enter the objective for Y axis display : ");
                    scanf("%d",&obj2);
                    if (obj2<1 || obj2>nobj)
                    {
                        printf("\n Wrong value of Y objective entered, value entered was %d\n",obj2);
                        exit(1);
                    }
                    printf("\n Enter the objective for Z axis display : ");
                    scanf("%d",&obj3);
                    if (obj3<1 || obj3>nobj)
                    {
                        printf("\n Wrong value of Z objective entered, value entered was %d\n",obj3);
                        exit(1);
                    }
                    printf("\n You have chosen 3D display, hence location of eye required \n");
                    printf("\n Enter the first angle (an integer in the range 0-180) (if not known, enter 60) :");
                    scanf("%d",&angle1);
                    if (angle1<0 || angle1>180)
                    {
                        printf("\n Wrong value for first angle entered, hence exiting \n");
                        exit(1);
                    }
                    printf("\n Enter the second angle (an integer in the range 0-360) (if not known, enter 30) :");
                    scanf("%d",&angle2);
                    if (angle2<0 || angle2>360)
                    {
                        printf("\n Wrong value for second angle entered, hence exiting \n");
                        exit(1);
                    }
                }
            }
        }
    }
    printf("\n Input data successfully entered, now performing initialization \n");
    return;
}
