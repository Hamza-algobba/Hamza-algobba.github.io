import matplotlib.pyplot as plt
import numpy as np
import constants as c

#read the samples from the file Data.txt
def read_samples(file_name):
    with open(file_name, 'r') as file:
        samples = [float(line) for line in file]
    return samples


#get the absolute value of each sample
def rectify_samples(samples):
    rectifiedSamples = [abs(sample) for sample in samples]
    return rectifiedSamples


#pick a part of the signal that is noise. get triple its standard deviation. This is our threshold for an MUAP
def calculate_threshold(sample, range_start, range_end):
    noiseSamples = []
    for i in range(range_start, range_end):
        noiseSamples.append(sample[i])
    threshold = 3 * np.std(noiseSamples)
    return threshold


#for each sample, get the average of the 20 samples surrounding it
def compute_average_adjacent(lst):
    result = []
    for i in range(len(lst)):
        start = max(0, i - int(c.T / 2))  # Ensure starting index is not negative
        end = min(len(lst), i + int(c.T / 2))  # Ensure ending index is within bounds
        adjacent_elements = lst[start:end]
        average = sum(adjacent_elements) / c.T
        result.append(average)
    return result


#get the starting and ending indices of all MUAPs
def extract_muaps(signal, threshold):
    MUAPs = []
    ind = 0
    while ind < len(signal):
        if signal[ind] > threshold:
            j = 0
            while signal[min(ind + j, len(signal) - 1)] > threshold: #make sure MUAP suration exeeds 20 samples
                if (j > 19) and (signal[ind + j + 1] < threshold):
                    MUAPs.append((ind, ind + j))
                    ind += j
                    break
                j += 1
        ind += 1
    return MUAPs


#compare each MUAP with MUAP templates, if square error exceeds the diff threshold create a new template
#if it matches a template update the template by averaging it with the current MUAP
def compareTemplate(muap, samples, templates, spectrums):  # ind is the starting index of each MUAP
    isolated_muap = samples[muap[0]: muap[1] + 1]
    max_index = isolated_muap.index(max(isolated_muap)) + muap[0]
    syncedMUAP = []
    for i in range(max_index - 10, max_index + 10):
        syncedMUAP.append(samples[i])
    matched = False  # bool to check whether muap matches an existing template
    D = []
    for k, v in templates.items():  # k is template muap number v is template muap values
        D.append(0)  # square error
        for i in range(1, c.T):
            D[k] += (syncedMUAP[i] - v[i]) ** 2
        if D[k] < c.DIFFTH:
            matched = True
            if(D[k] == min(D)):
	            for i in range(c.T):
	                v[i] = (syncedMUAP[i] + v[i]) / 2
	            spectrums[k].append(max_index)
	            bit_vector[k].append(muap)
    if not matched:
        templates[len(templates)] = syncedMUAP
        spectrums[len(spectrums)] = [max_index]
        bit_vector[len(bit_vector)] = [muap]



#execute the template comparison with all MUAPs
def compare_muaps(MUAPs, samples, templates, spectrums, bit_vector):
    for muap in MUAPs:
        compareTemplate(muap, samples, templates, spectrums)


#choose a segment from the signal to display
#for every MUAP present in the segment, place an asterix above the peak of the MUAP
#color code the asterixes depending on which template the MUAP belongs to 
def plot_annotated_segment(range_start, range_end, spectrums, muaps, samples):
	muaps_in_range = []
	muap_types = []
	muap_peaks = []
	for muap in muaps:
		isolated_muap = samples[muap[0]: muap[1] + 1]
		if(muap[0] >= range_start and muap[1] <= range_end):
			max_index = isolated_muap.index(max(isolated_muap)) + muap[0]
			muap_peaks.append(max_index - 30000)
			muaps_in_range.append(muap)
			for k, v in spectrums.items():
				if(max_index in v):
					muap_types.append(k)

	y = []
	for i in range(len(muaps_in_range)):
		y.append(1000)
	
	plt.scatter(muap_peaks, y, c=muap_types, cmap='viridis', marker = '*')
	plt.plot(original_samples[range_start:range_end])
	plt.title("detectingMUAP")
	plt.xlabel("Sample")
	plt.ylabel("Amplitude")
	#plt.legend()
	plt.show()



#generate k bit vectors, each one indicating the starting indices of each MUAP that matches given template
def generate_bit_vectors(bit_vector, original_samples, bit_vector2):
	for k, v in bit_vector.items():
		bit_vector2[k] = [0] * len(original_samples)
		for m in v:
			bit_vector2[k][m[0]] = 1
				



#plot the fast fourier transform frequency spectrum
def generate_fourier_frequencies(bit_vector2):
	for k, v in bit_vector2.items():
		y = np.fft.fft(bit_vector2[k])
		x = np.fft.fftfreq(len(original_samples)) 
		plt.scatter(x, abs(y))
		plt.title(f"Frequency spectrum for template #{k+1}")
		plt.xlabel("Frequency")
		plt.ylabel("Amplitude")
		plt.show()


def plot_templates(templates):
    for k, v in templates.items():
    	plt.title(f"template #{k+1}")
    	plt.xlabel("sample")
    	plt.ylabel("Amplitude")
    	plt.plot(v)
    	plt.show()



def plot_sample(sample):
    plt.plot(sample)
    plt.show()


original_samples = read_samples('Data.txt')
rectified_samples = rectify_samples(original_samples)
smoothed_samples = compute_average_adjacent(rectified_samples)
threshold = calculate_threshold(rectified_samples, 500, 900)

MUAPs = extract_muaps(smoothed_samples, threshold)

plot_sample(original_samples)
templates = {}
spectrums = {} #maps templates to peak values
bit_vector = {} #maps templates to muap span
bit_vector2 = {} #maps templates to muap peaks
compare_muaps(MUAPs, original_samples, templates, spectrums, bit_vector)
plot_templates(templates)
plot_annotated_segment(30000, 35000, spectrums, MUAPs, original_samples)
generate_bit_vectors(bit_vector, original_samples, bit_vector2)
generate_fourier_frequencies(bit_vector2)



