import sys
import pandas as pd
import matplotlib.pyplot as plt

def main():
    df = pd.read_csv(sys.argv[-1])
    plt.plot(df.iloc[:,0], df.iloc[:,1])
    plt.show()


if __name__ == "__main__":
    main()
