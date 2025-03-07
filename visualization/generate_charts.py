import os
import argparse

import pandas as pd
import matplotlib.pyplot as plt


def gen_charts(input_file, output_dir):
    """
    Generate charts for approximations.

    :param input_file: File with approximation comparisons.
    :param output_dir: Output directory for generated charts.
    """

    df = pd.read_csv(input_file)

    os.makedirs(output_dir, exist_ok=True)

    terms_values = df["terms"].unique()

    for terms in terms_values:
        print(f"Processing chart for approximations with {int(terms)} terms.")

        subset = df[df["terms"] == terms]

        plt.figure(figsize=(15, 10))

        # plot values
        angle = subset["angle"]
        value_approx, value_math, value_err = subset["approx_val"], subset["math.h_val"], subset["approx_err_abs"]

        plt.plot(angle, value_approx,   label="approx sin(x)",      linestyle="solid",  color="blue")
        plt.plot(angle, value_math,     label="math.h sin(x)",      linestyle="solid",  color="green")
        plt.plot(angle, value_err,      label="absolute error",     linestyle="solid",  color="red")

        # figure labels
        plt.title(f"Sine Approximation with {int(terms)} term{'s' if terms != 1 else ''}")

        plt.xlabel("Angle (radians)")
        plt.ylabel("Value")

        plt.grid()
        plt.legend()

        plt.savefig(f"{output_dir}/compare_sin_approx_{int(terms)}terms.png")
        plt.close()

    print("All plots generated for each terms value!")


if __name__ == "__main__":

    parser = argparse.ArgumentParser(description="Generate charts for approximations.")
    parser.add_argument("-i", "--input", type=str, default="../approx-comparison.csv", help="Input file with approximation comparisons.")
    parser.add_argument("-o", "--output", type=str, default="./out", help="Output directory for generated charts.")
    args = parser.parse_args()

    gen_charts(args.input, args.output)
