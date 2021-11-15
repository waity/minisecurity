#!/bin/bash
if [ ! -d yolo ]; then
  mkdir yolo
fi


cd yolo
if [ ! -f coco.names ]; then
  wget https://raw.githubusercontent.com/pjreddie/darknet/master/data/coco.names -q --show-progress
fi
if [ ! -f yolov3-tiny.cfg ]; then
  wget https://raw.githubusercontent.com/pjreddie/darknet/master/cfg/yolov3-tiny.cfg -q --show-progress
fi
if [ ! -f yolov3-tiny.weights ]; then
  wget https://pjreddie.com/media/files/yolov3-tiny.weights -q --show-progress
fi
