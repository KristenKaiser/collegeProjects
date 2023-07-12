import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import recall_score, f1_score, log_loss
from sklearn.metrics import multilabel_confusion_matrix
from sklearn.metrics import classification_report


OUTPUT_CAT = "parent_ed"
TEST_SIZE = 0.2
FILE_LOCATION = "exams.csv"


def minimize_confusion(multi):
    tp = 0
    fp = 0
    fn = 0
    tn = 0
    for i in multi:
        tp += i[0][0]
        fp += i[0][1]
        fn += i[1][0]
        tn += i[1][1]
    return tp, fp, fn, tn


def split_data(df):
    input_cats = []
    for col in df.columns:
        if col != OUTPUT_CAT:
            input_cats.append(col)

    x = df[input_cats].to_numpy(dtype=float)
    y = df[OUTPUT_CAT].to_numpy()
    # randomize and split data
    x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=TEST_SIZE)
    sc_x = StandardScaler()
    x_train = sc_x.fit_transform(x_train)
    x_test = sc_x.transform(x_test)
    return x_train, y_train, x_test, y_test, input_cats


def main():
    if __name__ == '__main__':
        df = pd.read_csv(FILE_LOCATION)
        x_train, y_train, x_test, y_test, input_cats = split_data(df)

        def run_case(neigh):
            def print_metrics(train_test, x, y):
                y_pred = neigh.predict(x)
                print(train_test)

                print(classification_report(y, y_pred))
                tp, fp, fn, tn = minimize_confusion(multilabel_confusion_matrix(y, y_pred,))
                print("\n mean of metrics")
                print("Accuracy: ", neigh.score(x, y))
                print("sensitivity: ", recall_score(y, y_pred, average="weighted"))
                print("specificity: ", tn/(tn + fp))
                print("F1 score: ", f1_score(y, y_pred, average="weighted"))
                print("log loss: ", log_loss(y, neigh.predict_proba(x)), "\n")

            neigh.fit(x_train, y_train)
            print_metrics("training", x_train, y_train)
            print_metrics("testing", x_test, y_test)

        neigh1 = KNeighborsClassifier(n_neighbors=3, weights="distance")
        run_case(neigh1)
        neigh2 = KNeighborsClassifier(n_neighbors=11, weights="distance")
        run_case(neigh2)
        neigh3 = KNeighborsClassifier(n_neighbors=100, weights="distance")
        run_case(neigh3)


if __name__ == '__main__':
    main()
