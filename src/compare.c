#include "stdlib.h"
#include "argp.h"
#include "stdbool.h"
#include "math.h"
#include "approximation.h"


/**************************\
|* Command line arguments *|
\**************************/

const char* argp_program_version = "TaylorSinApprox-Comparison 1.0";
static char doc[] = "Comparing Taylor series approximated sin(x) with math.h sin(x).";
static struct argp_option options[] = {
    { "lower-angle", 'l', "LOWER_BOUND_ANGLE", 0, "Lower bound angle in radians." },
    { "upper-angle", 'u', "UPPER_BOUND_ANGLE", 0, "Upper bound angle in radians." },
    { "step", 's', "STEP", 0, "Step size for angles." },
    { "output-file", 'o', "CSV_FILE", 0, "Export result to CSV file." },
    { "upper-terms", 't', "UPPER_BOUND_TERMS", 0, "Upper bound of number of terms in the Taylor series." },
    { "yes", 'y', 0, 0, "Yes to all, non-interactive mode." },
    { 0 }
};

struct arguments {
    double lowerAngle; // lower bound angle in radians
    double upperAngle; // upper bound angle in radians
    double step; // step size for angles
    char* csvFile; // output filename, NULL if not set
    int upperTerms; // upper bound of number of terms
    bool nonInteractive; // -y option
};


static error_t parse_opt(int key, char* arg, struct argp_state* state) {
    struct arguments* arguments = state->input;
    switch (key) {
        case 'l':
            arguments->lowerAngle = strtod(arg, NULL);
            break;
        case 'u':
            arguments->upperAngle = strtod(arg, NULL);
            break;
        case 's':
            arguments->step = strtod(arg, NULL);
            break;
        case 'o':
            arguments->csvFile = arg;
            break;
        case 't':
            arguments->upperTerms = (int) strtol(arg, NULL, 10);
            break;
        case 'y':
            arguments->nonInteractive = true;
            break;
        case ARGP_KEY_ARG:
            return 0;
        default:
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

static struct argp argp = { options, parse_opt, NULL, doc, 0, 0, 0 };



/**********\
|*  Main  *|
\**********/

int main(const int argc, char** argv) {

    struct arguments arguments = {
        .lowerAngle = -4 * PI,
        .upperAngle = 4 * PI,
        .step = 0.01,
        .csvFile = "approx-comparison.csv",
        .upperTerms = 10, // default term count
        .nonInteractive = false
    };

    argp_parse(&argp, argc, argv, 0, 0, &arguments);


    if (!arguments.csvFile) {
        fprintf(stderr, "Error: Output file not set.\n");
        return 1;
    }

    if (fopen(arguments.csvFile, "r") && !arguments.nonInteractive) {
        printf("File %s already exists. Overwrite? [y/n]: ", arguments.csvFile);
        char response;
        scanf(" %c", &response);

        if (response != 'y') {
            printf("Skipping...\n");
            return 0;
        }
    }

    FILE* file = fopen(arguments.csvFile, "w");

    if (!file) {
        fprintf(stderr, "Error: Unable to open file %s.\n", arguments.csvFile);
        return 1;
    }

    // print info to console
    printf("Running Taylor series approximation comparison for:\n");
    printf("- Terms: [1..%i]\n", arguments.upperTerms);
    printf("- Angle range: [%.10f..%.10f]\n", arguments.lowerAngle, arguments.upperAngle);
    printf("- Step size: %.10f\n", arguments.step);
    printf("- Output file: %s\n", arguments.csvFile);

    // write csv header
    fprintf(file, "terms,angle,approx_val,math.h_val,approx_err_abs\n");

    // iterate through angles for each term
    for (int term = 1; term <= arguments.upperTerms; ++term) {
        for (double angle = arguments.lowerAngle; angle <= arguments.upperAngle; angle += arguments.step) {
            const int terms = term;
            const double radians = angle;

            const double approxResult = taylorApproxSin(radians, terms);
            const double sinResult = sin(radians);

            const double errorAbs = fabs(approxResult - sinResult);

            fprintf(file, "%i,%.10f,%.10f,%.10f,%.10f\n", terms, radians, approxResult, sinResult, errorAbs);
        }
    }

    printf("Results exported to %s.\n", arguments.csvFile);

    return 0;
}
