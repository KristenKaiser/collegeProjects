import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error
from sklearn.metrics import mean_absolute_error
from sklearn.metrics import r2_score
from sklearn.neural_network import MLPRegressor


OUTPUT_CAT = "quality"
TEST_SIZE = 0.2
FILE_LOCATION = "winequality-all.csv"


def run_case(x_train, y_train, x_test, y_test, case):

    def print_metrics(reg, train_test, x, y):
        y_predict = reg.predict(x)
        mse = mean_squared_error(y, y_predict)
        mae = mean_absolute_error(y, y_predict)
        r2 = r2_score(y, y_predict)
        print(train_test, "set data:")
        print("MSE: ", mse)
        print("MAE: ", mae)
        print("R^2:", r2, "\n")

    model = case.fit(x_train, y_train)
    print_metrics(model, "training", x_train, y_train)
    print_metrics(model, "testing", x_test, y_test)
    print("________________________________________________")


def split_data(df):
    input_cats = []
    for col in df.columns:
        if col != OUTPUT_CAT:
            input_cats.append(col)

    x = df[input_cats].to_numpy(dtype=float)
    y = df[OUTPUT_CAT].to_numpy()
    # randomize and split data
    x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=TEST_SIZE)
    return x_train, y_train, x_test, y_test


def main():
    if __name__ == '__main__':
        df = pd.read_csv(FILE_LOCATION)
        x_train, y_train, x_test, y_test = split_data(df)

        test_case_1 = MLPRegressor(max_iter=10000, hidden_layer_sizes=(2048,))
        test_case_2 = MLPRegressor(max_iter=10000, hidden_layer_sizes=(1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, ))
        test_case_3 = MLPRegressor(max_iter=10000, hidden_layer_sizes=(256))
        print("case 1")
        print(test_case_1)
        run_case(x_train, y_train, x_test, y_test, test_case_1)
        print("case 2")
        print(test_case_2)
        run_case(x_train, y_train, x_test, y_test, test_case_2)
        print("case 3")
        print(test_case_3)
        run_case(x_train, y_train, x_test, y_test, test_case_3)


if __name__ == '__main__':
    main()
