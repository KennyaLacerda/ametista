#ifndef __SOLUCAO_H__
#define __SOLUCAO_H__

#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstdlib>

#include "instancia.h"

#define MANHA 0
#define TARDE 1
#define NOITE 2
#define FOLGA 3
#define THETA 100000
#define PI 0.46
#define LAMBDA 0.54



using namespace std;

struct Solucao{

	vector< vector<int> > schedule;   /// dia por turno
	Instancia* inst;
	float cost;
	int problemas;

	double s1;
	double s2;
	double h2;
	double h3;
	double h4;



	Solucao(Instancia* inst){
		s1 = 0;
		s2 = 0;
		h2 = 0;
		h3 = 0;
		h4 = 0;
		problemas = 0;
		cost = 0;


		this->inst = inst;

		int nurses = inst->nurses;
		int days = inst->days;
		int shifts = inst->shifts;

        for (int n=0; n<nurses;n++){
        	schedule.push_back(vector<int>());
        	schedule[n].resize(days, 0);
        	for (int d = 0; d < days; d++){
        		schedule[n][d] = rand() % shifts ;
           }
        }

        updateCost();

	}

	void print(){
		int nurses = inst->nurses;
		int days = inst->days;
		int shifts = inst->shifts;

        for (int n=0; n<nurses;n++){

        	for (int d = 0; d < days; d++){
				printf("%d ", schedule[n][d]);            }
            printf("\n");
        }

        printf(" problemas: %d \n",problemas);
        printf(" custo: %f \n",cost);
        printf(" s1: %f \n",s1);
        printf(" s2: %f \n",s2);
        printf(" h2: %f \n",h2);
        printf(" h3: %f \n",h3);
        printf(" h4: %f \n",h4);

	}


	void updateCost(){
		cost = 0;
		problemas = 0;

        
		// restrição s1
		s1 = 0;
		for (int n=0; n<inst->nurses;n++){
        	for (int d = 0; d < inst->days; d++){
				int shift = schedule[n][d];
				s1+= inst->preference[n][d][shift];
			}           
        }

       


        // restrição s2
       s2 = 0;

       for(int d=0; d < inst->days; d++){  // perecorrendo os dias
        	for (int s=0; s< inst->shifts; s++){ //percorrendo os turnos
        		int cont = 0;					
        		// contando o numero de infermeiros do turno S
        		for (int n = 0; n< inst->nurses; n++){
	        		int shift = schedule[n][d];

	        		if(shift == s)  
	        			cont++;	        		  	
	        	}
	        	if(cont > inst->coverage[d][s]){    // verifica se é maior que a corbertura
	        		int custo = cont - inst->coverage[d][s];
	        		s2 += custo*custo;   // valor quadratico
	        	}	
        	}
	    }


	     

	    // Restrição H1 satisfeita

	    // Restrição H2
	    h2 = 0;
	    for(int d=0; d < inst->days; d++){  // perecorrendo os dias
        	for (int s=0; s< inst->shifts; s++){ //percorrendo os turnos
        		int cont = 0;					
        		// contando o numero de infermeiros do turno S
        		for (int n = 0; n< inst->nurses; n++){
	        		int shift = schedule[n][d];

	        		if(shift == s)
	        			cont++;	        		  	
	        	}
	        	if(cont < inst->coverage[d][s]){    // verifica se é maior que a corbertura
	        		int custo = inst->coverage[d][s] - cont ;
	        		h2 += custo*custo;   // valor quadratico
	        	}	
        	}
	    }


	    // Restrição H3
	    h3 = 0;
	    for(int n =0; n< inst->nurses; n++){ // percorre cada enfermeiro
	    	for (int d = 0; d < inst-> days -1 ; d++){ // percorre cada dia menos o ultimo 
	    		if(schedule[n][d] == NOITE){        // analise se está no turno da noite
	    			if(schedule[n][d+1] != FOLGA)	// se esta analise se esta em folga no dia seguinte, se não estiver soma 1 ao custo
	    				h3++; 
	    		}
	    	}
	    }



		// Restrição H4 - No mínimo 1 folga não obrigatória a cada 7 dias
        h4 = 0;
        for(int n=0; n< inst->nurses; n++){       // percorre cada enfermeiro  
            for(int d = 0; d < inst->days - 6; d++){ // percorre os dias ate o d-6
                int folgas=0; // armazena qtd de dias com folga 
                for(int x = d; x<d+7; x++){   // percorre a cada sete posições
                    if(schedule[n][x] == FOLGA) {
                    	//Só conta folgas que não são obrigatórias
                    	if (x==0 || (x>0 && schedule[n][x-1]!=NOITE)) {
                    	folgas++;
                  	}
               }
            }
            if(folgas==0) // verifica variavel
            	h4++; // soma        
            }
        }
	   

	    // soma dos problemas
	    problemas = h2+ h3+ h4;

	    //SOMA DE TODOS OS CUSTOS

	    cost =  s1*PI + s2*LAMBDA + (h2+ h3+ h4)*THETA; 
        
	}




};

#endif