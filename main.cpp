
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <math.h>



#include "instancia.h"
#include "solucao.h"
#include "Crono.h"

#define INTERACAO 10000
int tempo =  300;


double simulated(Instancia* inst, Solucao* sol){
	Crono crono;
	Solucao best = *sol;
	double t =100;
	double bestCost = sol->cost;

	crono.run();
	while( t > 0 ){
		for(int i=0; i<INTERACAO; i++){

			int posEnf = rand() % inst->nurses;
			int posDia = rand() % inst-> days;
			int turnoDepois = rand() % inst->shifts;

			int turnoAntes = sol->schedule[posEnf][posDia]; // amazena valor antes de mudar
			double custoAntes = sol->cost;

			sol->schedule[posEnf][posDia] = turnoDepois; // muda o turno 
			sol->updateCost();  // atualiza o custo
			double custoDepois = sol->cost;  // armazen valor atualizado do custo

			double delta = custoDepois - custoAntes;

			if(delta < 0){
				if(custoDepois < best.cost){
					//bestCost = custoDepois;
					best = *sol;
				}
			}else{
				double p = (rand()%10000)/10000.0+0.00001; 
				// verifica a probabilidade de aceitação
				if(p >= pow(M_E, -delta/t)){
					sol->schedule[posEnf][posDia] = turnoAntes;
					sol->cost = custoAntes;
				} 
			}
		}
		t=t*0.98;
		//printf(" %f %f %f %f \n", best.cost, sol->cost, t, crono.getTime());		

		if(t < 0.001)
			break;

		if(crono.getTime() > tempo)
			break; 
	}
	printf(" %f %f %f %f \n", best.cost, sol->cost, t, crono.getTime());		
		
	*sol = best;
    return 0;
}

int main(int argc, char** argv) {
	tempo = atoi(argv[2]);
	srand((unsigned)time(0));

	Instancia inst;    
    inst.ler(argv[1]);

    Solucao sol(&inst);
    //sol.print();

    simulated(&inst, &sol);
    sol.print();





	return 0;
}