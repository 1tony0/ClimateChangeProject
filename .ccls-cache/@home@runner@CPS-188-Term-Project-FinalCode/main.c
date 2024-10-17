#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
  char dummy_char[10000] = {"Nothing"}; 
  double average_temps[7777], average_uncertainties[7777],maximum_temps[7777],minimum_temps[7777],maximum_uncertainties[7777],minimum_uncertainties[7777], land_and_ocean_temp[7777],land_and_ocean_uncertainty[7777]; //Various Arrays for initial data storage. The number does not matter. My favorite number is 7, therefore I put 7.
double summation,summation_max,summation_min,average_summation;

char curline[777], tempholder[777], date[7777][20]; 
char *token; 
int i=0,j=0,k=0;
double yearly_average_temperature[777], yearly_maximum_temperature[777], yearly_minimum_temperature[777],monthly_average_temperatures[12];

//All the answer to the questions ewill go here
  FILE* q1 = fopen("q1data.txt", "w");
  FILE* q2 = fopen("q2data.txt", "w");
  FILE* q3 = fopen("q3data.txt", "w");
  FILE* q4 = fopen("q4data.txt", "w");
  FILE* q5 = fopen("q5data.txt", "w");
  FILE* q6 = fopen("q6data.txt", "w");
  FILE* q7 = fopen("q7data.txt", "w");
  FILE* q8 = fopen("q8data.txt", "w");
  FILE* q9 = fopen("q9data.txt", "w");
  FILE* q10 = fopen("q10data.txt", "w");
  FILE* q11 = fopen("q11data.txt", "w");
  FILE* data = fopen("Data_Term_proj.txt", "r");
  FILE* raw = fopen("rawdata.txt", "w");
  if (!data){
    printf("File failed to open.");
    return(0);
  }

  fgets(dummy_char,500,data); //dumps first line
  while (!feof(data)) {
    
    fgets(curline,500,data);//current line
    token = strtok(curline," , ");  
    strcpy(date[i],token);//copies date from token into textholder
    token = strtok(NULL," , "); 
    average_temps[i]= atof(token);//pulls the temperature into array by taking token and converting to float
    
    if (i>=1200){
      
      token = strtok(NULL," , ");
      average_uncertainties[i] = atof(token);
      token = strtok(NULL," , ");
      maximum_temps[i] = atof(token);
      token = strtok(NULL," , ");
      maximum_uncertainties[i] = atof(token);
      token = strtok(NULL," , ");
      minimum_temps[i] = atof(token);
      token = strtok(NULL," , ");
      minimum_uncertainties[i] = atof(token);
      token = strtok(NULL," , ");
      land_and_ocean_temp[i] = atof(token);
      token = strtok(NULL," , ");
      land_and_ocean_uncertainty[i] = atof(token);
      
    }
    i+=1;

  }



    for (j = 0; j < i; j++) {
        fprintf(raw,"%s %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf %.3lf\n",date[j], average_temps[j],average_uncertainties[j],maximum_temps[j],maximum_uncertainties[j],minimum_temps[j],minimum_uncertainties[j],land_and_ocean_temp[j],land_and_ocean_uncertainty[j]);
    }
    fclose(raw);



    
//Question 1:
    for (j=10;j<(i/12);j++){//Extract Yearly Average Tempuratures
      
        average_summation = 0;
      
        for (k=0;k<12;k++){
          
          average_summation += average_temps[12*j+k];//using a little bit of math to find the proper cell to extract from and add to summation(j as year, k as month)
        }
      
        yearly_average_temperature[j] = average_summation/12.0; //divide by months per year to get average
        fprintf(q1,"%d %lf\n",(j+1750),yearly_average_temperature[j]);
        fprintf(q6,"%d %lf\n",(j+1750),yearly_average_temperature[j]);
      
    }
fclose(q1);




    
//Question 2: 
    double temp_18th_century, temp_19th_century, temp_20th_century, temp_21st_century;//century averages
  
    for (j=10;j<(i/12);j++){//Extract Yearly Average Tempuratures
        summation= 0;
        for (int k=0;k<12;k++){
          summation+= average_temps[12*j+k];//using a little bit of math to find the proper cell to extract from and add to summation(j as year, k as month)
        }
        yearly_average_temperature[j] = summation/12.0; //divide by months per year to get average 
    }
      summation= 0;
  
    for (j=10;j<50;j++){
        summation+= yearly_average_temperature[j];
    }
  
    temp_18th_century = summation/40.0;//finding average of first 40 years for 18th century
    summation= 0;
  
    for(j=50;j<150;j++){
        summation+= yearly_average_temperature[j];
    }
  
      temp_19th_century = summation/100.0;//finding average of next 100 years for 19th century
      summation= 0;
  
    for(j=150;j<250;j++){
      
        summation+= yearly_average_temperature[j];
      
    }
    temp_20th_century = summation/100.0;
    summation= 0;
  
    for(j=250; j<265;j++){
      
        summation+= yearly_average_temperature[j];
    }
    temp_21st_century = summation/15.0;
    
      fprintf(q2,"18th Century Average: %lf\n19th Century Average: %lf\n20th Century Average: %lf\n21st Century Average: %lf\n",temp_18th_century,temp_19th_century,temp_20th_century,temp_21st_century);
fclose(q2);



    
//Question 3:
    double q3monthly_average_temperatures[12], q3_summation_month; 
    char months[12][10]= {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    
      for(j = 0; j < 12; j++){
        
        q3_summation_month = 0;
        
        for(k = 150; k < 265; k++){
          
          q3_summation_month += average_temps[12*k+j];
          
        }
        q3monthly_average_temperatures[j] = q3_summation_month/115.0;

        fprintf(q3,"%s Average Temperature: %lf\n",months[j],q3monthly_average_temperatures[j]);
      }
fclose(q3);



    
//Question 4:
    double hottest_temp =0, coldest_temp=0; 
    int hottest_month, coldest_month;
    //Finding hottest and coldest months
    for(j = 0; j<i;j++){
      
        if (average_temps[j] > hottest_temp){
          
          hottest_temp = average_temps[j];
          hottest_month = j+1;
          
        }
        if (average_temps[j] < coldest_temp){
          
          coldest_temp = average_temps[j];
          coldest_month = j+1;
        }
      }
      fprintf(q4,"The hottest month is %s %d with a temperature of %lf.\nThe coldest month is %s %d with a temperature of %lf.",months[hottest_month%12-1], (hottest_month/12+1750),hottest_temp,months[coldest_month%12-1],(coldest_month/12+1750),coldest_temp);
fclose(q4);



    
//Question 5:
      //setting starting values
      double maximum_temp = -100, minimum_temp = 100;
      int year_maximum = 0, year_minimum = 0;
  
      for (int i = 10; i < 265; i++){
        
        if (maximum_temp < yearly_average_temperature[i]){
          
          maximum_temp = yearly_average_temperature[i];
          year_maximum = i;
        }
        else if (minimum_temp > yearly_average_temperature[i]){
          
        minimum_temp = yearly_average_temperature[i];
        year_minimum = i;
        }
      }
      fprintf(q5,"The hottest year was %d with a temperature of %lfºC.\nThe coldest year was %d with a temperature of %lfºC.", year_maximum + 1750, maximum_temp, year_minimum + 1750, minimum_temp);
fclose(q5);



    
//Question 6:
/*question 6 data is in q6 file, but question 6 is based on gnuplot.

This is the code that will be put into GNUPlot after saving the file to the GNUPlot website:

set title "Yearly Temperatures for the years 1760 to 2015"
set xrange [1760:2015]
set xlabel "Years"
set ylabel "Temperature (°C)"
plot "q6data.txt" using 1:2 with line title 'Yearly Temperatures (°C)'
*/

    
    
    
//Question 7:
    // Collecting data for both centuries
    fprintf(q7,"Year\t\tTemperature (19th century)\tTemperature (20th century)\n");
    for (j = 50; j < 150; j++) {
        fprintf(q7,"%d\t\t%lf\t\t\t%lf\n", (j - 50), yearly_average_temperature[j], yearly_average_temperature[j + 100]);
    }
    fclose(q7);
/*
Plug this into GNUPlot after saving q7data.txt file to the website:
        
#Set the title and labels
set title "Comparing Average Land Temperatures for 19th and 20th Centuries"
set xlabel "Years in the century"
set ylabel "Average Land Temperature (°C)"

#Plot the data from q7data.txt
plot "q7data.txt" using 1:2 with line title '19th Century Temperature'
replot "q7data.txt" using 1:3 with line title '20th Century Temperature'
*/

    
    
    
//Question 8:
    
    for (j=100;j<(i/12);j++){//q8 data
        summation_max = 0;
        summation_min = 0;
        for (k=0;k<12;k++){
          summation_max += maximum_temps[12*j+k];//using a little bit of math to find the proper cell to extract from and add to sum (j as year, k as month)
          summation_min += minimum_temps[12*j+k];
        }
            yearly_maximum_temperature[j] = summation_max/12.0; //divide by months per year to get average
        yearly_minimum_temperature[j] = summation_min    /12.0;
        fprintf(q8,"%d %lf %lf %lf\n",(j+1750),yearly_average_temperature[j],yearly_maximum_temperature[j], yearly_minimum_temperature[j]);
      }
/*
Plot this into GNUPlot after saving q8data.txt file to the website:


#Set the title and labels
set title 'Comparing LandAverageTemp, LandMaxTemp and LandMinTemp'
set xlabel "Years"
set ylabel "Temperature (°C)"

#Set the range
set xrange [1850:2015]
set yrange [0:20]

#Plot the data from q8data.txt
plot "q8data.txt" using 1:2 with lines title 'Land Average Temperature'
replot "q8data.txt" using 1:3 with lines title 'Land Max Temperature'
replot "q8data.txt" using 1:4 with lines title 'Land Min Temperature'
*/




    
//Question 9:
    double landavgtemp1, landmaxtemp1, landmintemp1;
      double landavgtemp2, landmaxtemp2, landmintemp2;
      double landavgtemp3, landmaxtemp3, landmintemp3;
      //data for 19th century after 1850
      average_summation = 0;
      summation_max = 0;
      summation_min = 0;
      for (j=0;j<50;j++){
        average_summation += yearly_average_temperature[j+100];
        summation_max += yearly_maximum_temperature[j+100];
        summation_min += yearly_minimum_temperature[j+100];
      }
      landavgtemp1 = average_summation/50.0;
      landmaxtemp1 = summation_max/50.0;
      landmintemp1 = summation_min/50.0;
      //data for 20th century 
      average_summation = 0;
      summation_max = 0;
      summation_min = 0;
      for (j=50;j<150;j++){
        average_summation += yearly_average_temperature[j+100];
        summation_max += yearly_maximum_temperature[j+100];
        summation_min += yearly_minimum_temperature[j+100];
      }
      landavgtemp2 = average_summation/100.0;
      landmaxtemp2 = summation_max/100.0;
      landmintemp2 = summation_min/100.0;
      //data for 21st century
      average_summation = 0;
      summation_max = 0;
      summation_min = 0;
      for (j=150;j<165;j++){
        average_summation += yearly_average_temperature[j+100];
        summation_max += yearly_maximum_temperature[j+100];
        summation_min += yearly_minimum_temperature[j+100];
      }
      landavgtemp3 = average_summation/15.0;
      landmaxtemp3 = summation_max/15.0;
      landmintemp3 = summation_min/15.0;

      fprintf(q9,"LandAvgTemps %lf %lf %lf\n", landavgtemp1, landavgtemp2, landavgtemp3);
      fprintf(q9,"LandMaxTemps %lf %lf %lf\n", landmaxtemp1, landmaxtemp2, landmaxtemp3);
      fprintf(q9,"LandMinTemps %lf %lf %lf\n", landmintemp1, landmintemp2, landmintemp3);
    fclose(q9);
/*
GNUplot script for question 9:

#Set the title and labels
set title "Temperatures per Century for Varying Data"
set style data histogram
set xlabel "Type of Temperature"
set ylabel "Avg Temp for Centuries (°C)"
set boxwidth 0.5

#Set the range
set yrange[0:20]

#Set the format for the y-axis


# Set the style for error bars


#Plot the data from data.txt
plot "q9data.txt" using 2:xtic(1) title "19th Century(After 1850)",\
"" using 2:xtic(1) title "20th Century",\
"" using 4:xtic(1) title "21st Century"
*/
    
    
    
    
//Question 10:
     for (j = 3000; j < i; j++){//data for q10

    fprintf(q10,"%.3lf %.3lf %.3lf\n", (1750+j/12.0), average_temps[j], average_uncertainties[j]); //Prints to file with uncertainties alongside
     }
    fclose(q10);
/*
GNUPlot script for question 10:

#Set the title and labels
set title 'Average Land Temperature With Error Bars (2000-2015)'
set xlabel "Years"
set ylabel "Average Temperature (°C)"

#Set the range
set yrange[0:20]

#Set the format for the y-axis


# Set the style for error bars


#Plot the data from data.txt
plot "q10data.txt" with errorbars title 'Uncertainties',"data.txt"with lines title 'Temperature'

*/

    
    
    
// Question 11:
      double yrlandoceantemp[500];

      for (j=100;j<(i/12);j++){//Extract Land Ocean Tempuratures
        average_summation = 0;
        for (k=0;k<12;k++){
              average_summation += land_and_ocean_temp[12*j+k];
        }
        yrlandoceantemp[j] = average_summation/12.0; //divide by months per year to get average
      }
      for (j=100;j<266;j++){
        fprintf(q11,"%d %lf %lf\n",(j+1750),yearly_average_temperature[j], yrlandoceantemp[j]);
      }
    fclose(q11);
/*
Gnuplot script for question 11:

#Set the title and labels
set title "Different Types of Temperatures from 1850 to 2015"

set xlabel "Year"
set ylabel " Temperature (°C)"

#Set the range
set key top right 
set yrange [6:20]
set xrange [1850:2015.99]


#Plot the data from data.txt
plot "q11data.txt" using 1:2 title "Land Average Temps" with lines lw 2 lc rgb "pink",""using 1:3 title "Land and Ocean Average Temps" with lines lw 4 lc rgb "black"
*/


      return 0;
    }

//This program is done by Antonio Souza.