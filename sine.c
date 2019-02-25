#include "vpi_user.h"
#include <math.h>

double sine(char * user_data) {
  vpiHandle systfref, args_iter,argh;
  systfref = vpi_handle(vpiSysTfCall, 0);
  args_iter = vpi_iterate(vpiArgument, systfref);
  argh = vpi_scan(args_iter);
  struct t_vpi_value argval;
  argval.format = vpiRealVal;
  vpi_get_value(argh, &argval);
  return sin(argval.value.real);
}

double cosine(char * user_data) {
  vpiHandle systfref, args_iter,argh;
  systfref = vpi_handle(vpiSysTfCall, 0);
  args_iter = vpi_iterate(vpiArgument, systfref);
  argh = vpi_scan(args_iter);
  struct t_vpi_value argval;
  argval.format = vpiRealVal;
  vpi_get_value(argh, &argval);
  return cos(argval.value.real);
}

uint32_t sine_size(char * user_data) {
  return 8*sizeof(double);
}

void registerSineFunc() {
  s_vpi_systf_data task_data_s;
  p_vpi_systf_data task_data_p = &task_data_s;
  task_data_p->type = vpiSysFunc;
  task_data_p->sysfunctype = vpiRealFunc;
  task_data_p->tfname = "$sine";
  task_data_p->calltf = sine;
  task_data_p->compiletf = 0;
  task_data_p->sizetf = sine_size;

  vpi_register_systf(task_data_p);
}

void registerCosineFunc() {
  s_vpi_systf_data task_data_s;
  p_vpi_systf_data task_data_p = &task_data_s;
  task_data_p->type = vpiSysFunc;
  task_data_p->sysfunctype = vpiRealFunc;
  task_data_p->tfname = "$cosine";
  task_data_p->calltf = cosine;
  task_data_p->compiletf = 0;
  task_data_p->sizetf = sine_size;

  vpi_register_systf(task_data_p);
}

void (*vlog_startup_routines[ ]) () = {
  registerSineFunc,
  registerCosineFunc,
  0
};
