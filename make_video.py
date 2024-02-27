import cv2
import os


def generate_video():
    image_folder = "outFrames/squareFrames/"

    video_name = "square_data.avi"
    images = [img for img in os.listdir(image_folder)]
    images = sorted(images, key=lambda x: int(x.split("_")[1].split(".png")[0]))

    frame = cv2.imread(os.path.join(image_folder, images[0]))

    # setting the frame width, height width

    # the width, height of first image

    height, width, layers = frame.shape

    video = cv2.VideoWriter(video_name, 0, 1, frameSize=(width, height), fps=24)

    # Appending the images to the video one by one

    for image in images:

        video.write(cv2.imread(os.path.join(image_folder, image)))

    # Deallocating memories taken for window creation

    cv2.destroyAllWindows()

    video.release()


generate_video()
