# STUB data set for now.
import math

import more_itertools


# will return the unique subsets of length from the org_set.
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
    for i in range(0, line_count):
        # mean = sum of all values / count of values
        val_sum = 0
        for j in range(1, feature_count+1):
            val_sum += list_of_features[i][j]
        mean.append(val_sum / feature_count)

    # now calculate the std for each feature
    std = []
    for i in range(0, line_count):
        # std = sqrt( (element - mean) ** 2 / num_features - 1)
        val_sum = 0
        for j in range(1, feature_count+1):
            # sum of element - mean ** 2
            # print(f"{list_of_features[i][j]}")
            val_sum += pow((list_of_features[i][j] - mean[i]), 2)
        variance = val_sum / (feature_count - 1)
        std.append(math.sqrt(variance))
        # print(f"MEAN: {mean[i]}")
        # print(f"VARIANCE: {variance}")
        # print(f"STD: {std[i]}\n")

    # package normalized data
    for i in range(0, line_count):
        for j in range(1, feature_count+1):
            list_of_features_normalized[i][j] = ((list_of_features[i][j] - mean[i]) / std[i])

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


def load_file_into_list2(file_name, feature_count):
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


# return our loaded data.
feature_list, feature_list_normalized, line_count = load_file_into_list2("CS170_Spring_2022_Large_data__97.txt", 40)

# get the features into individual columns
features = list(zip(*feature_list_normalized))

# our subset to use
subset = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
          31, 32, 33, 34, 35, 36, 37, 38, 39, 40]
subsets = more_itertools.set_partitions(subset)
best_acc = 0
best_sub = []
previous_subs = []
for x in subsets:
    seen = False
    for y in previous_subs:
        x.sort()
        if x == y:
            seen = True
            break
    if seen:
        continue
    current_acc = accuracy(feature_list_normalized, x[0], len(feature_list_normalized))
    if current_acc > best_acc:
        best_acc = current_acc
        best_sub = x[0]
        print(f"NEW BEST SUBSET: {best_sub} provides accuracy of {best_acc}")
    x.sort()
    previous_subs.append(x)

print(f"BEST SUBSET: {best_sub} provides accuracy of {best_acc}")
