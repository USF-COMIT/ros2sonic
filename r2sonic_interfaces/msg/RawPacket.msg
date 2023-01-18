# the frame_id corresponding to the unit
string frame_id

# the data associated with the packet in big-endian order
# stored as char so the human readable section names
# can be read in rqt-topic or ros2 topic echo.
char[] data
