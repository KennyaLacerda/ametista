#ifndef __INSTANCIA_H__
#define __INSTANCIA_H__

#include <string>
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

struct Instancia {

    int nurses; // N (numero de enfermeiros)
    int days; // D (numero de dia da escala)
    int shifts; // S (numero de turnos da escala)

    vector< vector<int> > coverage;       //coverage matrix 2d com days linhas x shift colunas
    vector< vector< vector<int> > > preference;   //preference matrix 3d [Nurse][day][shift]

    void ler(string arquivo) {
    	
    	FILE *arq = fopen(arquivo.c_str(), "rt");

        if(arq == NULL){
        	printf("Problemas na leitura do arquivo\n");
        	return;
        }else{
        	//lendo as dimensoes
            fscanf(arq,"%d %d %d", &nurses, &days, &shifts); 

            // lendo a cobertura
            for (int d=0; d<days; d++) {
                coverage.push_back(vector<int>());

                int s1, s2, s3, s4;

                fscanf(arq, "%d %d %d %d ", &s1, &s2, &s3, &s4);

                coverage[d].push_back(s1);
                coverage[d].push_back(s2);
                coverage[d].push_back(s3);
                coverage[d].push_back(s4); 

                //printf("%d %d %d %d \n",coverage[d][0], coverage[d][1],coverage[d][2], coverage[d][3] );
            }

            // lendo preferencias
            for (int n=0; n<nurses;n++){
                preference.push_back(vector< vector<int> >());
            	for (int d=0; d<days; d++) {
                    preference[n].push_back(vector<int>());
            		int s1, s2, s3, s4;
                    fscanf(arq, "%d %d %d %d ", &s1, &s2, &s3, &s4);

                    preference[n][d].push_back(s1);
                    preference[n][d].push_back(s2);
                    preference[n][d].push_back(s3);
                    preference[n][d].push_back(s3); 

                    //printf("%d %d %d  %d ",preference[n][d][0], preference[n][d][1],preference[n][d][2],preference[n][d][3]);
                }
                //printf("\n");

            }            
        }
    }    
};

#endif