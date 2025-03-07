#include "stdio.h"
#include "math.h"
#include "argp.h"
#include "stdbool.h"
#include "stdlib.h"
#include "approximation.h"


/**************************\
|* Command line arguments *|
\**************************/

const char* argp_program_version = "TaylorSinApprox 1.0";
static char doc[] = "A program for approximating sin(x) using Taylor series for Simulation course.";
static struct argp_option options[] = {
    { "degrees", 'd', "DEGREES", 0, "Angle in degrees." },
    { "radians", 'r', "RADIANS", 0, "Angle in radians." },
    { "output-file", 'o', "CSV_FILE", 0, "Export result to CSV file." },
    { "num-terms", 'n', "NUMBER_OF_TERMS", 0, "Number of terms in the Taylor series, default=100" },
    { "yes", 'y', 0, 0, "Yes to all, non-interactive mode." },
    { 0 }
};

struct arguments {
    double angle; // value of angle in degrees or radians
    bool isDegrees;
    bool isRadians;
    int terms; // number of terms
    char* csvFile; // output filename, NULL if not set
    bool nonInteractive; // -y option
};


static error_t parse_opt(int key, char* arg, struct argp_state* state) {
    struct arguments* arguments = state->input;
    switch (key) {
        case 'd':
            arguments->angle = strtod(arg, NULL);;
            arguments->isDegrees = true;
            break;
        case 'r':
            arguments->angle = strtod(arg, NULL);
            arguments->isRadians = true;
            break;
        case 'o':
            arguments->csvFile = arg;
            break;
        case 'n':
            arguments->terms = (int) strtol(arg, NULL, 10);
            if (arguments->terms <= 0) {
                argp_error(state, "Error: Number of terms must be greater than 0.");
            }
            break;
        case 'y':
            arguments->nonInteractive = true;
            break;
        case ARGP_KEY_ARG:
            return 0;
        default:
            return ARGP_ERR_UNKNOWN;
    }

    if (arguments->isDegrees && arguments->isRadians) {
        argp_error(state, "Error: Both degree and radians options are set, use only one of them.");
    }

    return 0;
}

static struct argp argp = { options, parse_opt, NULL, doc, 0, 0, 0 };



/**********\
|*  Main  *|
\**********/

int main(const int argc, char** argv) {

    struct arguments arguments = {
        .angle = 0.0,
        .isDegrees = false,
        .isRadians = false,
        .terms = 100, // default term count
        .csvFile = NULL,
        .nonInteractive = false
    };

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    // check if angle or radians is set
    if (!arguments.isDegrees && !arguments.isRadians) {
        fprintf(stderr, "Error: No angle or radians provided.\n"
                        "See --help for more information.\n");
        return 1;
    }

    const double radians = arguments.isDegrees ? arguments.angle * PI / 180 : arguments.angle; // if not degree, then radians (assured above)
    const int terms = arguments.terms;
    const double result = taylorApproxSin(radians, terms);

    printf("approx terms = %i\n", terms);

    printf("approx sin(%f) = %f\n", radians, result);
    printf("math.h sin(%f) = %f\n", radians, sin(radians));

    // handle file output
    if (arguments.csvFile) {

        // if file exists and -y is not set, ask for overwrite
        if (fopen(arguments.csvFile, "r") && !arguments.nonInteractive) {
            printf("File %s already exists. Overwrite? [y/n]: ", arguments.csvFile);
            char response;
            scanf(" %c", &response); // space before %c to ignore whitespace

            if (response != 'y') {
                printf("Skipping file export.\n");
                return 0;
            }
        }

        FILE* file = fopen(arguments.csvFile, "w");
        if (file) {
            fprintf(file, "radians,approx_terms,approx_result,math.h_value\n");
            fprintf(file, "%f,%i,%f,%f\n", radians, terms, result, sin(radians));
            fclose(file);
            printf("Result written to %s.\n", arguments.csvFile);
        } else {
            fprintf(stderr, "Error: Could not open file %s for writing.\n", arguments.csvFile);
        }
    }

    return 0;
}
