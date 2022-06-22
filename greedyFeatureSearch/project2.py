import math
from random import seed, uniform
import more_itertools


# will return the unique subsets of length from the org_set in a list.
def unique_subsets_of_length(length, org_set):
    subsets = more_itertools.set_partitions(org_set)
    remaining_subsets = list()
    # traverse all subsets.
    for list_of_subsets in subsets:
        for current_list_subset in list_of_subsets:
            if len(current_list_subset) == length:
                # convert current_list_subset to a tmp_set:
                tmp_set = set()
                for element in current_list_subset:
                    tmp_set.add(element)

                # add if none are in the remaining_subsets.
                if len(remaining_subsets) == 0:
                    remaining_subsets.append(tmp_set)
                # else we have to check if it already exists.
                else:
                    add_set = True
                    for subset in remaining_subsets:
                        # Test if this set already belongs.
                        if tmp_set == subset:
                            # print(f"EQUAL SETS! {tmp_set} == {subset}")
                            add_set = False
                    if add_set:
                        # print(f"ADDING SET! {tmp_set}")
                        remaining_subsets.append(tmp_set)
    return remaining_subsets


# will return a list of lists version of the file data and the number of lines found in the file.
# will also return a normalized version of the data in the same list format.
def load_file_into_list(file_name, feature_count):
    # fastest way to get file line count in python
    # source: https://stackoverflow.com/questions/845058/how-to-get-line-count-of-a-large-file-cheaply-in-python
    line_count = sum(1 for line in open(file_name))
    # Load the data from the file.
    file_data = open(file_name, "r")
    # store data into a list of list.
    list_of_features = [[] for i in range(line_count)]

    # how to load into 2D list
    # source: https://stackoverflow.com/questions/21238242/python-read-file-into-2d-list
    for i in range(line_count):
        list_of_features[i] = [float(j) for j in file_data.readline().split()]
    # also build one for the normalized version
    file_data.seek(0)
    list_of_features_normalized = [[] for i in range(line_count)]
    for i in range(line_count):
        list_of_features_normalized[i] = [float(j) for j in file_data.readline().split()]

    # normalize the data
    # first calculate the mean for each feature
    mean = []
    for i in range(1, feature_count + 1):
        sum_of_vals = 0
        for j in range(0, line_count):
            # print(f"{list_of_features[j][i]}")
            sum_of_vals += list_of_features[j][i]
        mean.append(sum_of_vals / line_count)
        # print(f"MEAN: {mean[i-1]}")

    # now calculate the std for each feature
    std = []
    for i in range(1, feature_count + 1):
        # std = sqrt( (element - mean) ** 2 / num_features - 1)
        sum_of_vals = 0
        for j in range(0, line_count):
            # sum of element - mean ** 2
            # print(f"{list_of_features[i][j]}")
            sum_of_vals += pow((list_of_features[j][i] - mean[i-1]), 2)
        variance = sum_of_vals / (line_count - 1)
        std.append(math.sqrt(variance))
        # print(f"MEAN: {mean[i-1]}")
        # print(f"VARIANCE: {variance}")
        # print(f"STD: {std[i-1]}\n")

    # package normalized data
    for i in range(1, feature_count+1):
        for j in range(0, line_count):
            list_of_features_normalized[j][i] = ((list_of_features[j][i] - mean[i-1]) / std[i-1])

    # return data
    return list_of_features, list_of_features_normalized, line_count


def accuracy(data, subset, line_count):
    number_right = 0
    for i in range(line_count):
        # i is the element that we leave out
        # calculate nearest neighbor
        nearestNeighbor = 0
        smallest_distance = 100000
        for j in range(line_count):
            # skip this element
            if j == i:
                pass
            else:
                distance = 0
                # add up all values for the feature subset online j
                for k in range(len(subset)):
                    # print(f"LINE: {j} POINT: {data[i][subset[k]]}")
                    distance += pow((data[j][subset[k]] - data[i][subset[k]]), 2)
                distance = math.sqrt(distance)
                # check if this is the new smallest distance found.
                #print(f"DISTANCE {distance} VS SMALLEST DISTANCE {smallest_distance}")
                if distance < smallest_distance:
                    nearestNeighbor = j
                    smallest_distance = distance
        # we now have our nearestNeighbor
        # we check to see if the classes are the same, and mark it right if they are.
        # print(f"CHECKING {data[nearestNeighbor][0]} VS {data[i][0]}")
        # print(f"{nearestNeighbor} VS {i}")
        if data[nearestNeighbor][0] == data[i][0]:
            number_right += 1

    # now we can calculate the accuracy for this feature subset.
    # print(f"NUMBER RIGHT: {number_right}")
    return (number_right / line_count) * 100


# STUB for now, returns a random floating point number from 0 to 100.
def cross_validation(data, current_set, feature_to_add):
    return round(uniform(0.0, 100.0), 2)


# Algorithms
def forward_selection(data):
    print("Starting Forward Selection!")

    # current features
    current_features = set()
    best_accuracy = 0

    # level of tree
    for i in range(1, len(data)+1):
        # print(f"On the {i}th level of the search tree")
        feature_to_add_at_this_level = None

        # feature loop
        change = False
        for j in range(1, len(data)+1):
            # check if we need to add this feature
            if j in current_features:
                continue

            # get accuracy from cross_validation function
            accuracy = cross_validation(data, feature_to_add_at_this_level, j)

            current_features.add(j)
            print(f"Using feature(s) {current_features} accuracy is {accuracy}%")
            # print(f"--Considering adding the {j} feature with accuracy of {current_features} being {accuracy}%")
            current_features.remove(j)

            # check if it's the new best accuracy.
            if accuracy > best_accuracy:
                best_accuracy = accuracy
                feature_to_add_at_this_level = j
                change = True

        # Add all items in feature_to_add_at_this_level into current_features set
        if feature_to_add_at_this_level is not None:
            current_features.add(feature_to_add_at_this_level)

        print(f"\nFeature set {current_features} was best, accuracy is {best_accuracy}%\n")
        # print(f"On level {i}, added feature {feature_to_add_at_this_level} to current set.")
        if not change:
            print("ACCURACY HAS NOT CHANGED, BEST SUBSET FOUND (May be local max)")
            break

    print(f"Finished search! The best feature subset is {current_features}, with an accuracy of {best_accuracy}%")


def backward_elimination(data):
    print("Starting Backward Elimination")

    # current features (not empty, but the full set)
    best_features = set()
    for i in data:
        best_features.add(i)
    best_accuracy = 0

    # walk down tree from the top subset.
    for i in range(len(data), 0, -1):
        print(f"On the {i}th level of the search tree")
        # get list of possible subsets.
        sub_list = unique_subsets_of_length(i, best_features)
        # walk down all possible subsets.
        change = False
        for j in sub_list:
            # get accuracy from cross_validation function
            accuracy = cross_validation(data, best_features, j)
            print(f"Using feature(s) {j} accuracy is {accuracy}%")
            # print(f"--Considering adding the {j} feature with accuracy of {current_features} being {accuracy}%")
            # check if it's the new best accuracy.
            if accuracy > best_accuracy:
                best_accuracy = accuracy
                best_features = j
                change = True

        if change is False and i != 1:
            print(f"LOWER ACCURACY FOUND, SEARCHING REST OF TREE IN CASE OF LOCAL MAX!")

        print(f"\nFeature set {best_features} was best, accuracy is {best_accuracy}%\n")
    print(f"Finished search! The best feature subset is {best_features}, with an accuracy of {best_accuracy}%")


# not implemented
def special_algo():
    print("STUB")


# Main Section of program.
print("Welcome to Mark Vincent's Feature Selection Algorithm!")
num_features = input("Please enter total number of features: ")
file_name = input("Please enter the file name: ")

# gather raw and normalized version of the data.
print("Normalizing the data!")
feature_list, feature_list_normalized, line_count = load_file_into_list("small-test-dataset.txt", 10)
print("Normalization complete!")

print("Please enter the type of algorithm you want to run:\n"
      "1: Forward Selection\n"
      "2: Backward Elimination\n"
      "3: Bertie's Special Algorithm")
algorithm_input = input()

# STUB data set for now.
data_set = {1, 2, 3, 4}

if algorithm_input == "1":
    forward_selection(data_set)
elif algorithm_input == "2":
    backward_elimination(data_set)
elif algorithm_input == "3":
    special_algo()
else:
    print("Bad input, exiting program.")
    exit(1)
