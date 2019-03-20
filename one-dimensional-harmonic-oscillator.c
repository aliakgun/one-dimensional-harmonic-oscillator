/**
 * @file classical-harmonic-oscillator
 * @author ali akgun
 * @date 19.03.2019
 * @brief One dimensional harmonic oscillator.
 * *Program description
 * ================================================
 * Generates position,force,velocity of the harmonic oscillator due to time.
 * Due to the forward derivative velocity and
 * position of the particle in one dimension can be
 * represented as:
 * F=ma,a=F/m
 * a=dv/dt>>>>>>>>vi=((vi+1)-vi)/h
 * v=dx/dt>>>>>>>>vi=((xi+1)-xi)/h
 * V(i+1)=Vi+(Fi/m)*h, h is the time step.
 * x(i+1)=xi+Vi*h
 * Program Requirements
 * ================================================
 * 1)Initial velocity and position.
 * 2)Time step.
 * 3)Force.
 * 4)Mass.
 * Program Algorithm:
 * ================================================
 * 1)Get the initial velocity and position of the
 * particle.
 * 2)Get the h(time step) and time interval.
 * 3)Get the F and m.
 * 4)Calculate the x(i+1) and V(i+1)
 * 5)Print them to the screen.
 * @bug velocity(initial) due to time is not correct
 * @todo Output to file
 * Print the v and x to the separate files.
 * External force menu
 * Please chose the force acting to the particle:
 * 1)-kx
 * 2)x
 * 3)x^2
 * Documentation of the code.
 */

#include<stdio.h>///For standard input output organisation.

typedef struct{
    double initial_position,
           initial_velocity,
           time_step,
           time_interval,
           mass,
           spring_constant,
           position,
           velocity,
           force;
}particle_t;

void drive(particle_t *particle);
void calculate_force(particle_t *particle);
void calculate_velocity(particle_t *particle);
void calculate_position(particle_t *particle);
void print(particle_t *particle,FILE *outp);
int main(){
    FILE *outp;
    particle_t particle;
    drive(&particle);
    print(&particle,outp);
}
/**
 * @param particle(specifier address of the particle_t type)
 * @brief Interacts with the user.
 * @return void
 */
void drive(particle_t *particle){
    printf("Velocity and position calculator for 1 dimensional particle system. F=-kx default\n");
    printf("Please enter the initial position of the particle.\n");
    scanf(" %lf",&(*particle).initial_position);
    printf("Please enter the initial velocity of the particle.\n");
    scanf(" %lf",&(*particle).initial_velocity);
    printf("Please enter the time step of the movement.\n");
    scanf(" %lf",&(*particle).time_step);
    printf("Please enter the time interval of the movement.\n");
    scanf(" %lf",&(*particle).time_interval);
    printf("Please enter the mass of the particle\n");
    scanf(" %lf",&(*particle).mass);
    printf("Please enter the spring constant(k)\n");
    scanf(" %lf",&(*particle).spring_constant);
}
/**
 * @param particle(specifier address of the particle_t type)
 * @brief Calculates force acting to the particle.
 * F = -kx
 * @see classical-harmonic-oscillator.pdf
 * @return void
 */
void calculate_force(particle_t *particle){
    (*particle) . force = -((*particle) . spring_constant * (*particle) . position);
}
/**
 * @param particle(specifier address of the particle_t type)
 * @brief Calculates velocity of the particle.
 * Vf = Vi + at , a = F / m
 * @see classical-harmonic-oscillator.pdf
 * @return void
 */
void calculate_velocity(particle_t *particle){
    calculate_force(particle);
    (*particle) . velocity = ((*particle) . velocity) + (((*particle) . force) / ((*particle) . mass)) * ((*particle) . time_step);
}
/**
 * @param  particle(specifier address of the particle_t type)
 * @brief Calculates position of the particle
 * Xf=Xi + Vt
 * @see Classical-harmonic-oscillator.pdf
 * @return void
 */
void calculate_position(particle_t *particle){
    ((*particle) . position) = ((*particle) . position) + ((*particle) . velocity) * ((*particle) . time_step);
}
/**
 * @param particle(specifier address of the particle_t type)
 * @brief sets initial conditions of the particle.
 * @see Classical-harmonic-oscillator.pdf
 * @return void
 */
void set_initial_conditions(particle_t *particle){
    (*particle) . position = (*particle) . initial_position;
    (*particle) . velocity=(*particle) . initial_velocity;
}
/**
 * @param particle(specifier address of the particle_t type)
 * @brief Calculates position,force and velocity due to time.
 * @see Classical-harmonic-oscillator.pdf
 * @return void
 */
void calculator(particle_t *particle){
    calculate_velocity(particle);
    calculate_position(particle);
    calculate_force(particle);
}
/**
 * @param particle(specifier address of the particle_t type)
 * @brief
 *
 * @return void
 */
void print(particle_t *particle,FILE *outp){
    outp = fopen("output.txt","w");
    set_initial_conditions(particle);
    fprintf(outp,"%s %18s %16s %11s","Force","Position","Velocity","Time\n");
    for (double i = (*particle) . time_step;i <= (*particle) . time_interval;i = i + (*particle) . time_step){
        calculator(particle);
        fprintf(outp,"%lf\t%lf\t%lf\t%lf\n",(*particle) . force,(*particle) . position,(*particle) . velocity,i);
    }//end
}
