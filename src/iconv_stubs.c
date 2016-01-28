
#include "iconv.h"

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <caml/mlvalues.h>
#include <caml/fail.h>
#include <caml/callback.h>
#include <caml/memory.h>
#include <caml/alloc.h>

void raise_error (char *msg) {
        caml_raise_with_string (*caml_named_value ("iconv_exn"), msg);
}

CAMLprim value
stub_iconv_convert (value ic, value oc, value input) {
        CAMLparam3 (ic, oc, input);
        CAMLlocal1 (output);
        char *r_input, *r_output, *r_output_start;
        iconv_t cd;

        size_t inputsz = caml_string_length (input);
        size_t outputsz = inputsz*8;
        size_t outputleft = outputsz;
        r_input = String_val (input);

        r_output = (char *)malloc (outputsz);
        if (!r_output) {
                raise_error ("cannot allocate memory for iconv()");
        }
        
        r_output_start = r_output;
        
        cd = iconv_open (String_val(oc), String_val(ic));
        
        if (cd == (iconv_t)-1) {
                free(r_output_start);
                raise_error ("iconv_open() failed");
        } else {
                int rc = iconv(cd, (const char **)&r_input, &inputsz, &r_output, &outputleft);
                iconv_close(cd);
                if (rc == -1) {
                        free(r_output_start);
                        raise_error ("iconv() failed");
                } else {
                        size_t outputbytes = outputsz - outputleft;

                        output = caml_alloc_string (outputbytes);
                        memcpy( String_val(output), r_output_start, outputbytes );
                        free(r_output_start);
                }
        }

        CAMLreturn (output);
}
