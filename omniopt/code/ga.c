#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdlib.h>

#include "global.h"
#include "rand.h"

int main(int argc, char **argv)
{
    int i;
    FILE *fpt1;
    FILE *fpt2;
    FILE *fpt3;
    FILE *fpt4;
    FILE *fpt5;
	FILE *fpt6;
    FILE *fpt;
	FILE *fpt7;
    FILE *gp;
    char *s;
    population *parent_pop;
    population *child_pop;
    population *mixed_pop;
    printf("\n Omni-optimizer code developed at KanGAL, IIT Kanpur.");
    printf("\n Copyright (C) 2006 by Dr. Kalyanmoy Deb and Santosh Tiwari");
	printf("\n");
	fflush(stdout);
    if (argc!=2)
    {
		printf("\n Usage: %s random_seed \n",argv[0]);
        exit(1);
    }
    seed = (double)atof(argv[1]);
    if (seed<=0.0 || seed>=1.0)
    {
        printf("\n Entered seed value is wrong, seed value must be in (0,1) \n");
        exit(1);
    }
    input();
	pdefinit();
    if (run_mode==0)
    {
        gp = popen(GNUPLOT_COMMAND,"w");
        if (gp==NULL)
        {
            printf("\n Could not open a pipe to gnuplot, check the definition of GNUPLOT_COMMAND in file global.h\n");
            printf("\n Edit the string to suit your system configuration, recompile and rerun the program\n");
            exit(1);
        }
    }
    fpt1 = fopen("initial_pop.out","w");
    fpt2 = fopen("final_pop.out","w");
    fpt3 = fopen("nondominated_pop.out","w");
    fpt4 = fopen("output.out","w");
    fpt5 = fopen("problem_data.out","w");
	fpt6 = fopen("plot.out","w");
	fpt7 = fopen("run.out","a");
    s = (char *)malloc(100*sizeof(double));
    output (fpt1, fpt2, fpt3, fpt4, fpt5);
    parent_pop = (population *)malloc(sizeof(population));
    child_pop = (population *)malloc(sizeof(population));
    mixed_pop = (population *)malloc(sizeof(population));
    allocate_memory_pop (parent_pop, popsize);
    allocate_memory_pop (child_pop, popsize);
    allocate_memory_pop (mixed_pop, 2*popsize);
    randomize();
    initialize_pop (parent_pop);
    decode_pop(parent_pop);
    printf("\n Initialization done, now performing first generation");
    fflush(stdout);
    evaluate_pop (parent_pop);
    define_epsilon (parent_pop, popsize, epsilon);
    assign_rank_and_crowding_distance (parent_pop);
    report_pop (parent_pop, fpt1);
    if (run_mode==0)
    {
        onthefly_display(parent_pop, gp, 1);
        fprintf(fpt4,"# gen = 1\n");
        report_pop(parent_pop,fpt4);
    }
	printf("\n gen = 1");
	fflush(stdout);
    fflush(fpt1);
    fflush(fpt2);
    fflush(fpt3);
    fflush(fpt4);
    fflush(fpt5);
    if (ngen==1)
    {
        printf("\n Generations finished, now reporting solutions");
        report_pop(parent_pop,fpt2);
        report_feasible(parent_pop,fpt3);
		report_obj(parent_pop,fpt6);
        fprintf(fpt5,"\n Number of crossover of real variable = %d",nrealcross);
        fprintf(fpt5,"\n Number of crossover of binary variable = %d",nbincross);
        fprintf(fpt5,"\n Number of mutation of real variable = %d",nrealmut);
        fprintf(fpt5,"\n Number of mutation of binary variable = %d",nbinmut);
    }
    else
    {
        for (i=2; i<=ngen; i++)
        {
            if (mate==0)
            {
                selection (parent_pop, child_pop);
            }
            else
            {
                restricted_selection(parent_pop, child_pop);
            }
            mutation_pop (child_pop);
            decode_pop(child_pop);
            evaluate_pop(child_pop);
            merge (parent_pop, child_pop, mixed_pop);
            define_epsilon (mixed_pop, 2*popsize, epsilon);
            fill_nondominated_sort (mixed_pop, parent_pop);
            if (run_mode==0)
            {
                onthefly_display(parent_pop, gp, i);
                fprintf(fpt4,"# gen = %d\n",i);
                report_pop(parent_pop,fpt4);
                fflush(fpt4);
            }
            if (i%frequency==0 && i>=frequency)
            {
                sprintf(s,"pop_var_%d_.out",i);
                fpt = fopen(s,"w");
                report_var(parent_pop,fpt);
                fflush(fpt);
                fclose(fpt);
            }
			printf("\n gen = %d",i);
        }
        printf("\n Generations finished, now reporting solutions");
        report_pop(parent_pop,fpt2);
        report_feasible(parent_pop,fpt3);
		report_obj(parent_pop,fpt6);
        fprintf(fpt5,"\n Number of crossover of real variable = %d",nrealcross);
        fprintf(fpt5,"\n Number of crossover of binary variable = %d",nbincross);
        fprintf(fpt5,"\n Number of mutation of real variable = %d",nrealmut);
        fprintf(fpt5,"\n Number of mutation of binary variable = %d",nbinmut);
    }
	fprintf(fpt7,"%f\t%e\n",seed,parent_pop->ind[0].obj[0]);
	fflush(fpt7);
	fclose(fpt7);
    fflush(stdout);
    fflush(fpt1);
    fflush(fpt2);
    fflush(fpt3);
    fflush(fpt4);
    fflush(fpt5);
	fflush(fpt6);
    fclose(fpt1);
    fclose(fpt2);
    fclose(fpt3);
    fclose(fpt4);
    fclose(fpt5);
	fclose(fpt6);
    free (epsilon);
    free (min_obj);
    free (max_obj);
    if (nreal!=0)
    {
        free (min_realvar);
        free (max_realvar);
    }
    if (nbin!=0)
    {
		free (nbits);
        free (min_binvar);
        free (max_binvar);
    }
	free(s);
	if (run_mode==0)
	{
		if (gp!=NULL)
		{
			pclose(gp);
		}
	}
	deallocate_memory_pop (parent_pop, popsize);
	deallocate_memory_pop (child_pop, popsize);
	deallocate_memory_pop (mixed_pop, 2*popsize);
	free(parent_pop);
	free(child_pop);
	free(mixed_pop);
    printf("\n Routine successfully exited \n");
    return (0);
}
