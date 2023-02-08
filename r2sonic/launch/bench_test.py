import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node
def generate_launch_description():
    ld = LaunchDescription()
    config = os.path.join(
        get_package_share_directory('r2sonic'),
        'params',
        'bench_test.yaml'
        )

    node=Node(
        package =       'r2sonic',
        name =          'r2sonic',
        executable =    'r2sonic_node',
        parameters = [config]
    )
    ld.add_action(node)
    return ld
