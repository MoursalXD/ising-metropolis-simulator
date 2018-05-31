#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 100      // grid size
#define runs 10   // number of Monte Carlo simulations


// returns up (1) or down (-1)
int updown()
{
  double randomNumber;
  randomNumber = drand48();
  if (randomNumber < 0.5) return (-1);
  else return 1;
}


// Calculate energy
double energy(int spin[N][N])
{ 
  int i,j;
  double E=0.;

  for (i=0; i<N; i++)
    for (j=0; j<N; j++)
    {
      if (i-1>=0) E -= 0.5*(spin[i][j]*spin[i-1][j]-1.);
      if (j-1>=0) E -= 0.5*(spin[i][j]*spin[i][j-1]-1.);
      if (i+1<N)  E -= 0.5*(spin[i][j]*spin[i+1][j]-1.);
      if (j+1<N)  E -= 0.5*(spin[i][j]*spin[i][j+1]-1.);
    }

  return E;    
}


int main()
{
  int i,j,run,spin[N][N],spinAccum[N][N][N];
  double en_old,en_new,H,r;
  srand48(5123);
  FILE *data;

  // initial fill
  for (i=0; i<N; i++)
  {
    for (j=0; j<N; j++)
    {
      spin[i][j] = updown();
      spinAccum[0][i][j] = spin[i][j];
    }
  }
  



  // METROPOLIS ALGORITHM
  for(run = 0; run<runs; run++)
  {
  for (i=0; i<N; i++)
    for (j=0; j<N; j++)
    {
      en_old = energy(spin);  // energy before flip

      // flip
      spin[i][j] = -spin[i][j];
 
      en_new = energy(spin);  // energy after flip
      H = en_new - en_old;    // difference in energy

      if (H>0)
      {
        r = drand48();
        if (r>exp(-H)) spin[i][j] = -spin[i][j];  // Undo flip
      }   
   	  spinAccum[run+1][i][j] = spin[i][j];
    }
    printf("Completed run #%i\n",run);
  }








  // output
  data = fopen("ising-output.dat","w");
  for (i=0; i<N; i++)
    for (j=0; j<N; j++)
      for (run=0; run<=runs; run++)
        if (spinAccum[run][i][j]==1) fprintf(data,"%i\t%i\t%i\n",run,i,j);
  fclose(data);

  

  return 0;
}
