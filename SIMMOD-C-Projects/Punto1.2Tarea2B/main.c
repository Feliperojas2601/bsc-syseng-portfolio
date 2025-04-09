/* External definitions for Punto 2.5. */
#include "simlib.h" /* Required for use of simlib.c. */
#define EVENT_ARRIVAL 1 /* Event type for arrival of box. */
#define EVENT_START 2  /* Event type for start box service. */
#define EVENT_END_SERVICE 3 /* Event type for end of box service. */
#define EVENT_CHECK 4
#define LIST_BAND 1 /* List number for BAND queue. */
#define LIST_SERVICE 2
#define STREAM_ARRIVAL 1 /* Random-number stream for arrival of product 1 times. */
#define STREAM_END_SERVICE 2 /* Random-number stream for download times. */
#define STREAM_BOXES 3
/* Declare non-simlib global variables. */
int num_boxes,num_boxes_ready,num_boxes_lost,num_boxes_queue,service_busy, boxes_required, time_required, band_distance, urgent_box;
float velocity,band_velocity,incremental, box_distance, service_distance, mean_service, standar_desviation, max_velocity; // Velocity in m/s
FILE *infile, *outfile;
/* Declare non-simlib functions. */

void arrive(void);
void start_service(void);
void end_service(void);
void report(void);
float getNormal(float, float);

main() /* Main function. */
{
 /* Open input and output files. */
 infile = fopen("carga.in", "r");
 outfile = fopen("carga.out", "w");
 /* Read input parameters. */
 fscanf(infile, "%d %d %d %f %f %f %f %f %f %f",
 &boxes_required,&time_required,&band_distance,&band_velocity, &max_velocity,&incremental,&box_distance,
 &service_distance,&mean_service,&standar_desviation);
 /* Write report heading and input parameters. */
 fprintf(outfile, "Band Model\n\n");
 fprintf(outfile, "Band Distance %9d \n\n",band_distance);
 fprintf(outfile, "Number of boxes required %9d \n\n",boxes_required);
 fprintf(outfile, "Velocity of band %11.3f m/s\n\n", band_velocity);
 fprintf(outfile, "Incremental %11.3f m/s \n\n", incremental);
 fprintf(outfile, "Max velocity %11.3f m/s \n\n", max_velocity);
 fprintf(outfile, "Box distance %11.3f m\n\n", box_distance);
 fprintf(outfile, "Service distance %11.3f m\n\n", service_distance);
 fprintf(outfile, "Mean service %11.3f secs\n\n", mean_service);
 fprintf(outfile, "Standar Desviation service %11.3f secs\n\n", standar_desviation);
 //fprintf(outfile, "Number of hours processed%12d\n\n\n", time_required);
 /* Initialize simlib */
 init_simlib();
 /* Set maxatr = max(maximum number of attributes per record, 4) */
 maxatr = 4; /* NEVER SET maxatr TO BE SMALLER THAN 4. */

 /* Run the simulation until it terminates. */
 //time_required = time_required*60;
 for( velocity = band_velocity ;velocity < max_velocity; velocity += incremental){
      /* Initialize the non-simlib statistical counter. */
     sim_time = 0;
     num_boxes_ready = 0;
     num_boxes_lost = 0;
     service_busy=0;
     urgent_box =0;
     num_boxes = 0;
     num_boxes_queue = 0;
      /* Schedule the first arrival. */
     event_schedule(sim_time,EVENT_ARRIVAL);
     do{
         /* Determine the next event. */
         timing();
         /* Invoke the appropriate event function. */
         switch (next_event_type) {
         case EVENT_ARRIVAL:
         arrive();
         break;
         case EVENT_START:
         start_service();
         break;
         case EVENT_END_SERVICE:
         end_service();
         break;
         case EVENT_CHECK:
         check();
         break;
     }
     }while(num_boxes_ready + num_boxes_lost <boxes_required);
     report();
 }
 fclose(infile);
 fclose(outfile);
 return 0;
}
void arrive() /* Event function for arrival of box to Band after arrival time. */
{
 float box_distance_expon = expon(box_distance,STREAM_BOXES);
 /* Place the arriving product at the end of the Band.
 Note that the following attributes are stored for each job record:
 1. Time of arrival to Band*/
 transfer[1] = sim_time;
 list_file(LAST,1);
 event_schedule(sim_time + (box_distance_expon/velocity),EVENT_ARRIVAL);
 event_schedule(sim_time + ((band_distance-service_distance)/velocity),EVENT_START);
}
void start_service() /* Event function to start a service. */
{
  float mean = getNormal(mean_service,standar_desviation);
  if(service_busy == 0){
    list_remove(FIRST,1);
    service_busy = 1;
    transfer[2] = sim_time + mean;
    list_file(FIRST, 2);
    event_schedule(sim_time + mean,EVENT_END_SERVICE);  //SOLO FALTA LA DISTR NORMAL
  }else{
    //urgent_box=1;
    event_schedule(sim_time, EVENT_CHECK);
    //num_boxes_lost++;
  }
}

void check()
{
    float remaining_time;
    list_remove(FIRST,2);
    remaining_time = transfer[2]-sim_time;
    if(remaining_time*velocity > 30 || remaining_time*velocity < 0){
        num_boxes_lost++;
    }else{
        event_schedule(transfer[2],EVENT_START);
    }
}

void end_service(void) /* Event function to end a download. */
{
    service_busy=0;
    num_boxes_ready++;
}

void report(void) /* Report generator function. */
{

 /* Get and write out estimates of desired measures of performance. */
 fprintf(outfile, "Number of hours processed: %10.3f \n", sim_time/3600);
 fprintf(outfile, "Band Velocity: %10.3f m/s \n", velocity);
 fprintf(outfile, "Number of boxes: %5d \n", num_boxes_ready+num_boxes_lost);
 fprintf(outfile, "Number of boxes completed: %5d \n", num_boxes_ready);
 fprintf(outfile, "Number of boxes lost : %5d \n", num_boxes_lost);
 fprintf(outfile, "Number of boxes completed per hour: %10.3f \n", num_boxes_ready/(sim_time/3600));
 fprintf(outfile, "Number of boxes lost per hour: %10.3f \n", num_boxes_lost/(sim_time/3600));
 fprintf(outfile, "Diference of boxes completed and lost per hour: %10.3f \n \n \n", num_boxes_ready/(sim_time/3600) - num_boxes_lost/(sim_time/3600));
}

float getNormal(float m,float v){
    float u1,u2,w,mult;
    float X1,X2;
    do{
        u1=uniform(-1,1,3);
        u2=uniform(-1,1,3);
        w= pow(u1,2) + pow(u2,2);
    }while (w>=1||w==0);

    mult=sqrt((-2*log (w))/w);
    X1=u1*mult;
    X2=u2*mult;

    return (m+v*(float)X1);
}


