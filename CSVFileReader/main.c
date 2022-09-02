/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/main.c to edit this template
 */

/* 
 * File:   main.c
 * Author: brash
 *
 * Created on September 1, 2022, 10:41 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE 80

const char* getfield(char* line, int num)
{
    const char* tok;
    for (tok = strtok(line, ",");
            tok && *tok;
            tok = strtok(NULL, ",\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

/*
 * 
 */
int main(int argc, char** argv) {
    
    const unsigned int nMax = 1000;
    
    FILE* inFile = NULL; //This variable will be a "pointer" to the input file
    FILE* outFile = NULL; //This variable will be a "pointer" to the output file
    
    char lastName[nMax][LINE], firstName[nMax][LINE];
    int score1[nMax],score2[nMax],score3[nMax];
    char letterGrade[nMax];
    double scoreAvg[nMax];
    double test1Average,test2Average,test3Average;
    
    /* Get the filename from the user */  
    char filename[LINE];
    printf("Enter the filename:\n");
    
    //gets(filename);
    // Note:  gets will work, and you will see it in a lot of
    // code, but it has been deprecated in C11, so we probably should not use it
    // anymore.
    // 
    // Instead, we will use scanf.  The format code is weird!
    // Explanation : Here, [] is the scanset character. ^\n tells to take 
    // input until newline doesn’t get encountered. Then, with this %*c, it 
    // reads newline character and here used * indicates that this 
    // newline character is discarded.
    
    //scanf("%[^\n]%*c", filename);
    //printf("Filename = %s\n",filename);
    
    /* Open the file for reading */
    //inFile = fopen(filename, "r");
    inFile = fopen("StudentInfo.csv", "r");
    
    if (inFile == NULL) {
        printf("Error:  Could not open file:  %s\n",filename);
        exit(-1);
    } else {
        printf("File opened successfully ... \n");
    }
    
    char line[LINE]; //char array to hold each "line" read from the file
    
    int j=0;  // This will hold the row number
    
    while (EOF != fscanf(inFile, "%s", line)) {
        
        //printf("%s\n",line);
        //printf("%d %d\n",i,j);
        
        // Read and parse line, with commas as separators
        
        strncpy(lastName[j],getfield(strdup(line),1),LINE);     
        strncpy(firstName[j],getfield(strdup(line),2),LINE);        
        score1[j]=atoi(getfield(strdup(line),3));
        score2[j]=atoi(getfield(strdup(line),4));              
        score3[j]=atoi(getfield(strdup(line),5));     
        
        j++;
        
    }
    
    outFile = fopen("report.txt", "w");
    
    int sum1=0,sum2=0,sum3=0;
    for (int idx=0;idx<j;idx++) {
        
        sum1=sum1+score1[idx];
        sum2=sum2+score2[idx];
        sum3=sum3+score3[idx];
        
        scoreAvg[idx] = (score1[idx]+score2[idx]+score3[idx])/3.0;
        
        if (scoreAvg[idx] >= 90.0) {
            letterGrade[idx] = 'A';
        } else {
            if (scoreAvg[idx] >= 80.0) {
                letterGrade[idx] = 'B';
            } else {
                if (scoreAvg[idx] >= 70.0) {
                    letterGrade[idx] = 'C';
                } else {
                    if (scoreAvg[idx] >= 60.0) {
                        letterGrade[idx] = 'D';
                    } else {
                        letterGrade[idx] = 'F';
                    }
                }
            }
        }
        
        fprintf(stdout,"%s\t%s\t%d\t%d\t%d\t%c\n",lastName[idx],firstName[idx],score1[idx],score2[idx],score3[idx],letterGrade[idx]);
        fprintf(outFile,"%s\t%s\t%d\t%d\t%d\t%c\n",lastName[idx],firstName[idx],score1[idx],score2[idx],score3[idx],letterGrade[idx]);
    }
    
    fprintf(stdout,"\n");
    fprintf(outFile,"\n");
    
    test1Average = (double)sum1/j;
    test2Average = (double)sum2/j;
    test3Average = (double)sum3/j;
    
    fprintf(stdout,"Averages: midterm1 %4.2f, midterm2 %4.2f, final %4.2f\n",test1Average,test2Average,test3Average);
    fprintf(outFile,"Averages: midterm1 %4.2f, midterm2 %4.2f, final %4.2f\n",test1Average,test2Average,test3Average);
    
    fclose(inFile);
    fclose(outFile);
    
}
