#include "trexio.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int test_write_mo_temperature(const char* file_name, const back_end_t backend) {

/* Try to write a finite electronic temperature for the molecular orbitals */

  trexio_t* file = NULL;
  trexio_exit_code rc;

  const int mo_num = 4;
  const double electronic_temperature = 300.0 * 3.166811563e-6;

/*================= START OF TEST ==================*/

  file = trexio_open(file_name, 'w', backend, &rc);
  assert (file != NULL);

  rc = trexio_has_mo_electronic_temperature(file);
  assert (rc == TREXIO_HAS_NOT);

  rc = trexio_write_mo_num(file, mo_num);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_write_mo_electronic_temperature(file, electronic_temperature);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}


static int test_read_mo_temperature(const char* file_name, const back_end_t backend) {

/* Try to read a finite electronic temperature from the TREXIO file */

  trexio_t* file = NULL;
  trexio_exit_code rc;

  double electronic_temperature = 0.0;
  const double expected = 300.0 * 3.166811563e-6;
  const double tolerance = 1.e-14;

/*================= START OF TEST ==================*/

  file = trexio_open(file_name, 'r', backend, &rc);
  assert (file != NULL);

  rc = trexio_has_mo_electronic_temperature(file);
  assert (rc == TREXIO_SUCCESS);

  rc = trexio_read_mo_electronic_temperature(file, &electronic_temperature);
  assert (rc == TREXIO_SUCCESS);
  assert (fabs(electronic_temperature - expected) < tolerance);

  rc = trexio_close(file);
  assert (rc == TREXIO_SUCCESS);

/*================= END OF TEST ==================*/

  return 0;
}


int main(void) {

/*============== Test launcher ================*/

  int rc;
  rc = RM_COMMAND_RESULT;
  assert (rc == 0);

  test_write_mo_temperature (TREXIO_FILE, TEST_BACKEND);
  test_read_mo_temperature  (TREXIO_FILE, TEST_BACKEND);

  rc = RM_COMMAND_RESULT;
  assert (rc == 0);

  return 0;
}
