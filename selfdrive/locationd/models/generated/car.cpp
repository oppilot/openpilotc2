#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                       Code generated with SymPy 1.12                       *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_2644101976798126494) {
   out_2644101976798126494[0] = delta_x[0] + nom_x[0];
   out_2644101976798126494[1] = delta_x[1] + nom_x[1];
   out_2644101976798126494[2] = delta_x[2] + nom_x[2];
   out_2644101976798126494[3] = delta_x[3] + nom_x[3];
   out_2644101976798126494[4] = delta_x[4] + nom_x[4];
   out_2644101976798126494[5] = delta_x[5] + nom_x[5];
   out_2644101976798126494[6] = delta_x[6] + nom_x[6];
   out_2644101976798126494[7] = delta_x[7] + nom_x[7];
   out_2644101976798126494[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5103817808636296269) {
   out_5103817808636296269[0] = -nom_x[0] + true_x[0];
   out_5103817808636296269[1] = -nom_x[1] + true_x[1];
   out_5103817808636296269[2] = -nom_x[2] + true_x[2];
   out_5103817808636296269[3] = -nom_x[3] + true_x[3];
   out_5103817808636296269[4] = -nom_x[4] + true_x[4];
   out_5103817808636296269[5] = -nom_x[5] + true_x[5];
   out_5103817808636296269[6] = -nom_x[6] + true_x[6];
   out_5103817808636296269[7] = -nom_x[7] + true_x[7];
   out_5103817808636296269[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_7118780548876508596) {
   out_7118780548876508596[0] = 1.0;
   out_7118780548876508596[1] = 0;
   out_7118780548876508596[2] = 0;
   out_7118780548876508596[3] = 0;
   out_7118780548876508596[4] = 0;
   out_7118780548876508596[5] = 0;
   out_7118780548876508596[6] = 0;
   out_7118780548876508596[7] = 0;
   out_7118780548876508596[8] = 0;
   out_7118780548876508596[9] = 0;
   out_7118780548876508596[10] = 1.0;
   out_7118780548876508596[11] = 0;
   out_7118780548876508596[12] = 0;
   out_7118780548876508596[13] = 0;
   out_7118780548876508596[14] = 0;
   out_7118780548876508596[15] = 0;
   out_7118780548876508596[16] = 0;
   out_7118780548876508596[17] = 0;
   out_7118780548876508596[18] = 0;
   out_7118780548876508596[19] = 0;
   out_7118780548876508596[20] = 1.0;
   out_7118780548876508596[21] = 0;
   out_7118780548876508596[22] = 0;
   out_7118780548876508596[23] = 0;
   out_7118780548876508596[24] = 0;
   out_7118780548876508596[25] = 0;
   out_7118780548876508596[26] = 0;
   out_7118780548876508596[27] = 0;
   out_7118780548876508596[28] = 0;
   out_7118780548876508596[29] = 0;
   out_7118780548876508596[30] = 1.0;
   out_7118780548876508596[31] = 0;
   out_7118780548876508596[32] = 0;
   out_7118780548876508596[33] = 0;
   out_7118780548876508596[34] = 0;
   out_7118780548876508596[35] = 0;
   out_7118780548876508596[36] = 0;
   out_7118780548876508596[37] = 0;
   out_7118780548876508596[38] = 0;
   out_7118780548876508596[39] = 0;
   out_7118780548876508596[40] = 1.0;
   out_7118780548876508596[41] = 0;
   out_7118780548876508596[42] = 0;
   out_7118780548876508596[43] = 0;
   out_7118780548876508596[44] = 0;
   out_7118780548876508596[45] = 0;
   out_7118780548876508596[46] = 0;
   out_7118780548876508596[47] = 0;
   out_7118780548876508596[48] = 0;
   out_7118780548876508596[49] = 0;
   out_7118780548876508596[50] = 1.0;
   out_7118780548876508596[51] = 0;
   out_7118780548876508596[52] = 0;
   out_7118780548876508596[53] = 0;
   out_7118780548876508596[54] = 0;
   out_7118780548876508596[55] = 0;
   out_7118780548876508596[56] = 0;
   out_7118780548876508596[57] = 0;
   out_7118780548876508596[58] = 0;
   out_7118780548876508596[59] = 0;
   out_7118780548876508596[60] = 1.0;
   out_7118780548876508596[61] = 0;
   out_7118780548876508596[62] = 0;
   out_7118780548876508596[63] = 0;
   out_7118780548876508596[64] = 0;
   out_7118780548876508596[65] = 0;
   out_7118780548876508596[66] = 0;
   out_7118780548876508596[67] = 0;
   out_7118780548876508596[68] = 0;
   out_7118780548876508596[69] = 0;
   out_7118780548876508596[70] = 1.0;
   out_7118780548876508596[71] = 0;
   out_7118780548876508596[72] = 0;
   out_7118780548876508596[73] = 0;
   out_7118780548876508596[74] = 0;
   out_7118780548876508596[75] = 0;
   out_7118780548876508596[76] = 0;
   out_7118780548876508596[77] = 0;
   out_7118780548876508596[78] = 0;
   out_7118780548876508596[79] = 0;
   out_7118780548876508596[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_8523961075882839653) {
   out_8523961075882839653[0] = state[0];
   out_8523961075882839653[1] = state[1];
   out_8523961075882839653[2] = state[2];
   out_8523961075882839653[3] = state[3];
   out_8523961075882839653[4] = state[4];
   out_8523961075882839653[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8000000000000007*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_8523961075882839653[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_8523961075882839653[7] = state[7];
   out_8523961075882839653[8] = state[8];
}
void F_fun(double *state, double dt, double *out_9009684528294757171) {
   out_9009684528294757171[0] = 1;
   out_9009684528294757171[1] = 0;
   out_9009684528294757171[2] = 0;
   out_9009684528294757171[3] = 0;
   out_9009684528294757171[4] = 0;
   out_9009684528294757171[5] = 0;
   out_9009684528294757171[6] = 0;
   out_9009684528294757171[7] = 0;
   out_9009684528294757171[8] = 0;
   out_9009684528294757171[9] = 0;
   out_9009684528294757171[10] = 1;
   out_9009684528294757171[11] = 0;
   out_9009684528294757171[12] = 0;
   out_9009684528294757171[13] = 0;
   out_9009684528294757171[14] = 0;
   out_9009684528294757171[15] = 0;
   out_9009684528294757171[16] = 0;
   out_9009684528294757171[17] = 0;
   out_9009684528294757171[18] = 0;
   out_9009684528294757171[19] = 0;
   out_9009684528294757171[20] = 1;
   out_9009684528294757171[21] = 0;
   out_9009684528294757171[22] = 0;
   out_9009684528294757171[23] = 0;
   out_9009684528294757171[24] = 0;
   out_9009684528294757171[25] = 0;
   out_9009684528294757171[26] = 0;
   out_9009684528294757171[27] = 0;
   out_9009684528294757171[28] = 0;
   out_9009684528294757171[29] = 0;
   out_9009684528294757171[30] = 1;
   out_9009684528294757171[31] = 0;
   out_9009684528294757171[32] = 0;
   out_9009684528294757171[33] = 0;
   out_9009684528294757171[34] = 0;
   out_9009684528294757171[35] = 0;
   out_9009684528294757171[36] = 0;
   out_9009684528294757171[37] = 0;
   out_9009684528294757171[38] = 0;
   out_9009684528294757171[39] = 0;
   out_9009684528294757171[40] = 1;
   out_9009684528294757171[41] = 0;
   out_9009684528294757171[42] = 0;
   out_9009684528294757171[43] = 0;
   out_9009684528294757171[44] = 0;
   out_9009684528294757171[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_9009684528294757171[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_9009684528294757171[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_9009684528294757171[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_9009684528294757171[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_9009684528294757171[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_9009684528294757171[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_9009684528294757171[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_9009684528294757171[53] = -9.8000000000000007*dt;
   out_9009684528294757171[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_9009684528294757171[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_9009684528294757171[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_9009684528294757171[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_9009684528294757171[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_9009684528294757171[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_9009684528294757171[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_9009684528294757171[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_9009684528294757171[62] = 0;
   out_9009684528294757171[63] = 0;
   out_9009684528294757171[64] = 0;
   out_9009684528294757171[65] = 0;
   out_9009684528294757171[66] = 0;
   out_9009684528294757171[67] = 0;
   out_9009684528294757171[68] = 0;
   out_9009684528294757171[69] = 0;
   out_9009684528294757171[70] = 1;
   out_9009684528294757171[71] = 0;
   out_9009684528294757171[72] = 0;
   out_9009684528294757171[73] = 0;
   out_9009684528294757171[74] = 0;
   out_9009684528294757171[75] = 0;
   out_9009684528294757171[76] = 0;
   out_9009684528294757171[77] = 0;
   out_9009684528294757171[78] = 0;
   out_9009684528294757171[79] = 0;
   out_9009684528294757171[80] = 1;
}
void h_25(double *state, double *unused, double *out_4448529349347489364) {
   out_4448529349347489364[0] = state[6];
}
void H_25(double *state, double *unused, double *out_923482510342953898) {
   out_923482510342953898[0] = 0;
   out_923482510342953898[1] = 0;
   out_923482510342953898[2] = 0;
   out_923482510342953898[3] = 0;
   out_923482510342953898[4] = 0;
   out_923482510342953898[5] = 0;
   out_923482510342953898[6] = 1;
   out_923482510342953898[7] = 0;
   out_923482510342953898[8] = 0;
}
void h_24(double *state, double *unused, double *out_7820867798992105906) {
   out_7820867798992105906[0] = state[4];
   out_7820867798992105906[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4481408109145277034) {
   out_4481408109145277034[0] = 0;
   out_4481408109145277034[1] = 0;
   out_4481408109145277034[2] = 0;
   out_4481408109145277034[3] = 0;
   out_4481408109145277034[4] = 1;
   out_4481408109145277034[5] = 0;
   out_4481408109145277034[6] = 0;
   out_4481408109145277034[7] = 0;
   out_4481408109145277034[8] = 0;
   out_4481408109145277034[9] = 0;
   out_4481408109145277034[10] = 0;
   out_4481408109145277034[11] = 0;
   out_4481408109145277034[12] = 0;
   out_4481408109145277034[13] = 0;
   out_4481408109145277034[14] = 1;
   out_4481408109145277034[15] = 0;
   out_4481408109145277034[16] = 0;
   out_4481408109145277034[17] = 0;
}
void h_30(double *state, double *unused, double *out_3314735907473183077) {
   out_3314735907473183077[0] = state[4];
}
void H_30(double *state, double *unused, double *out_3441815468850202525) {
   out_3441815468850202525[0] = 0;
   out_3441815468850202525[1] = 0;
   out_3441815468850202525[2] = 0;
   out_3441815468850202525[3] = 0;
   out_3441815468850202525[4] = 1;
   out_3441815468850202525[5] = 0;
   out_3441815468850202525[6] = 0;
   out_3441815468850202525[7] = 0;
   out_3441815468850202525[8] = 0;
}
void h_26(double *state, double *unused, double *out_3084305609940666069) {
   out_3084305609940666069[0] = state[7];
}
void H_26(double *state, double *unused, double *out_2818020808531102326) {
   out_2818020808531102326[0] = 0;
   out_2818020808531102326[1] = 0;
   out_2818020808531102326[2] = 0;
   out_2818020808531102326[3] = 0;
   out_2818020808531102326[4] = 0;
   out_2818020808531102326[5] = 0;
   out_2818020808531102326[6] = 0;
   out_2818020808531102326[7] = 1;
   out_2818020808531102326[8] = 0;
}
void h_27(double *state, double *unused, double *out_5280377804493369926) {
   out_5280377804493369926[0] = state[3];
}
void H_27(double *state, double *unused, double *out_1267052157049777614) {
   out_1267052157049777614[0] = 0;
   out_1267052157049777614[1] = 0;
   out_1267052157049777614[2] = 0;
   out_1267052157049777614[3] = 1;
   out_1267052157049777614[4] = 0;
   out_1267052157049777614[5] = 0;
   out_1267052157049777614[6] = 0;
   out_1267052157049777614[7] = 0;
   out_1267052157049777614[8] = 0;
}
void h_29(double *state, double *unused, double *out_2600894846260679259) {
   out_2600894846260679259[0] = state[1];
}
void H_29(double *state, double *unused, double *out_3952046813164594709) {
   out_3952046813164594709[0] = 0;
   out_3952046813164594709[1] = 1;
   out_3952046813164594709[2] = 0;
   out_3952046813164594709[3] = 0;
   out_3952046813164594709[4] = 0;
   out_3952046813164594709[5] = 0;
   out_3952046813164594709[6] = 0;
   out_3952046813164594709[7] = 0;
   out_3952046813164594709[8] = 0;
}
void h_28(double *state, double *unused, double *out_3930123937982873884) {
   out_3930123937982873884[0] = state[0];
}
void H_28(double *state, double *unused, double *out_1130352203904935865) {
   out_1130352203904935865[0] = 1;
   out_1130352203904935865[1] = 0;
   out_1130352203904935865[2] = 0;
   out_1130352203904935865[3] = 0;
   out_1130352203904935865[4] = 0;
   out_1130352203904935865[5] = 0;
   out_1130352203904935865[6] = 0;
   out_1130352203904935865[7] = 0;
   out_1130352203904935865[8] = 0;
}
void h_31(double *state, double *unused, double *out_6537655960113173927) {
   out_6537655960113173927[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3444228910764453802) {
   out_3444228910764453802[0] = 0;
   out_3444228910764453802[1] = 0;
   out_3444228910764453802[2] = 0;
   out_3444228910764453802[3] = 0;
   out_3444228910764453802[4] = 0;
   out_3444228910764453802[5] = 0;
   out_3444228910764453802[6] = 0;
   out_3444228910764453802[7] = 0;
   out_3444228910764453802[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_2644101976798126494) {
  err_fun(nom_x, delta_x, out_2644101976798126494);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5103817808636296269) {
  inv_err_fun(nom_x, true_x, out_5103817808636296269);
}
void car_H_mod_fun(double *state, double *out_7118780548876508596) {
  H_mod_fun(state, out_7118780548876508596);
}
void car_f_fun(double *state, double dt, double *out_8523961075882839653) {
  f_fun(state,  dt, out_8523961075882839653);
}
void car_F_fun(double *state, double dt, double *out_9009684528294757171) {
  F_fun(state,  dt, out_9009684528294757171);
}
void car_h_25(double *state, double *unused, double *out_4448529349347489364) {
  h_25(state, unused, out_4448529349347489364);
}
void car_H_25(double *state, double *unused, double *out_923482510342953898) {
  H_25(state, unused, out_923482510342953898);
}
void car_h_24(double *state, double *unused, double *out_7820867798992105906) {
  h_24(state, unused, out_7820867798992105906);
}
void car_H_24(double *state, double *unused, double *out_4481408109145277034) {
  H_24(state, unused, out_4481408109145277034);
}
void car_h_30(double *state, double *unused, double *out_3314735907473183077) {
  h_30(state, unused, out_3314735907473183077);
}
void car_H_30(double *state, double *unused, double *out_3441815468850202525) {
  H_30(state, unused, out_3441815468850202525);
}
void car_h_26(double *state, double *unused, double *out_3084305609940666069) {
  h_26(state, unused, out_3084305609940666069);
}
void car_H_26(double *state, double *unused, double *out_2818020808531102326) {
  H_26(state, unused, out_2818020808531102326);
}
void car_h_27(double *state, double *unused, double *out_5280377804493369926) {
  h_27(state, unused, out_5280377804493369926);
}
void car_H_27(double *state, double *unused, double *out_1267052157049777614) {
  H_27(state, unused, out_1267052157049777614);
}
void car_h_29(double *state, double *unused, double *out_2600894846260679259) {
  h_29(state, unused, out_2600894846260679259);
}
void car_H_29(double *state, double *unused, double *out_3952046813164594709) {
  H_29(state, unused, out_3952046813164594709);
}
void car_h_28(double *state, double *unused, double *out_3930123937982873884) {
  h_28(state, unused, out_3930123937982873884);
}
void car_H_28(double *state, double *unused, double *out_1130352203904935865) {
  H_28(state, unused, out_1130352203904935865);
}
void car_h_31(double *state, double *unused, double *out_6537655960113173927) {
  h_31(state, unused, out_6537655960113173927);
}
void car_H_31(double *state, double *unused, double *out_3444228910764453802) {
  H_31(state, unused, out_3444228910764453802);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
