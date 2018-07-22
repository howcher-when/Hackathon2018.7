# -*- coding: utf-8 -*-
import face_recognition
import cv2
import serial

video_capture = cv2.VideoCapture(0)
ser = serial.Serial('/dev/ttyUSB1')

executor_img = []
executor_face_encoding = []
executor_img.append(face_recognition.load_image_file("cmz.jpg"))
executor_img.append(face_recognition.load_image_file("whc.jpg"))
executor_face_encoding.append(face_recognition.face_encodings(executor_img[0])[0])
executor_face_encoding.append(face_recognition.face_encodings(executor_img[1])[0])

face_locations = []
face_encodings = []
face_names = []
process_this_frame = True

while True:
    ret, frame = video_capture.read()

    small_frame = cv2.resize(frame, (0, 0), fx=0.25, fy=0.25)

    if process_this_frame:
        face_locations = face_recognition.face_locations(small_frame)
        face_encodings = face_recognition.face_encodings(small_frame, face_locations)

        face_names = []
        executor_exist = False
        for face_encoding in face_encodings:
            executor = False
            match = face_recognition.compare_faces(executor_face_encoding, face_encoding, 0.4)
            for face in match:
                if face:
                    executor = True
                    executor_exist = True
                    break
            if executor:
                name = "executor"
            else:
                name = "unknown"
            face_names.append(name)
        if executor_exist:
            ser.write(b'1')
        else:
            ser.write(b'0')

    process_this_frame = not process_this_frame

    for (top, right, bottom, left), name in zip(face_locations, face_names):
        top *= 4
        right *= 4
        bottom *= 4
        left *= 4

        cv2.rectangle(frame, (left, top), (right, bottom), (0, 0, 255),  2)

        cv2.rectangle(frame, (left, bottom - 35), (right, bottom), (0, 0, 255), 2)
        font = cv2.FONT_HERSHEY_DUPLEX
        cv2.putText(frame, name, (left+6, bottom-6), font, 1.0, (255, 255, 255), 1)

    cv2.imshow('Video', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

video_capture.release()
cv2.destroyAllWindows()
