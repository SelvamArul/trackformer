"""
Generate additional attributes seq_length, first_frame_image_id, track_id from the ycbv in COCO format
NOTE: YCBV is already in COCO format
"""

import json
import pandas as pd
from pathlib import Path as P
import argparse

def main(args):
    src = P(args.src)
    with open(src) as js:
        data = json.load(js)

    import ipdb; ipdb.set_trace()
    print ('Done')

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Generate MOT COCO dataset from BOP COCO')
    parser.add_argument('--src', help='source file in BOP format', 
            default='/home/user/periyasa/workspace/6d_pose/datasets/ycbv_coco/annotations/instances_test.json')
    parser.add_argument('--tgt', help='name of the target file to be written',
            default='/tmp/instance_test_MOT.json')
    args = parser.parse_args()
    main(args)
