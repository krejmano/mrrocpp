include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(ui
	../MAM_wnd_manual_moves_automatic_measure.cc
	../abmain.cc
	../fun.cc
	../fun_r_conveyor.cc
	../fun_r_irp6_mechatronika.cc
	../fun_r_irp6_on_track.cc
	../fun_r_irp6_postument.cc
	../fun_r_irp6ot_tfg.cc
	../fun_r_irp6p_tfg.cc
	#../fun_r_polycrank.cc
	../fun_r_shead.cc
	../fun_r_smb.cc
	../fun_r_speaker.cc
	../fun_r_spkm.cc
	../threads.cc
	../timer.cc
	../ui.cc
	../ui_ecp_r_common.cc
	../ui_ecp_r_irp6_common.cc
	../ui_ecp_r_speaker.cc
	../ui_ecp_r_tfg_and_conv.cc
	../ui_init.cc
	../wndFileLocationEvents.cc
	../wndForceControlEvents.cc
	../wndTrajectoryReproduceEvents.cc
)

find_library(PHEX_LIBRARY phexlib $ENV{QNX_TARGET}/x86/usr/lib)
find_library(AP_LIBRARY Ap $ENV{QNX_TARGET}/x86/usr/lib)
find_library(PH_LIBRARY ph $ENV{QNX_TARGET}/x86/usr/lib)
set(PHOTON_LIBRARIES ${PHEX_LIBRARY} ${AP_LIBRARY} ${PH_LIBRARY})

set(ROBOT_LIBRARIES
	ecp_r_irp6ot ecp_r_irp6p
	ecp_r_irp6ot_tfg ecp_r_irp6p_tfg
	ecp_r_irp6m ecp_r_conv
	ecp_r_polycrank
	ecp_r_speaker
	ecp_r_smb ecp_r_spkm ecp_r_shead
)

target_link_libraries(ui
	${ROBOT_LIBRARIES}
	ecp
	${PHOTON_LIBRARIES}
	${COMMON_LIBRARIES}
)

ADD_CUSTOM_COMMAND(
	OUTPUT ui.stage2
	COMMAND $ENV{QNX_HOST}/usr/bin/usemsg ${CMAKE_CURRENT_BINARY_DIR}/ui ${CMAKE_CURRENT_SOURCE_DIR}/../Usemsg
	COMMAND cmake -E touch ui.stage2
	DEPENDS ui ${CMAKE_CURRENT_SOURCE_DIR}/../Usemsg
)

set(ABMOD Icon.wgti MAM_wnd_manual_moves_automatic_measures.wgtw base.wgtw
	file_selection_window.wgtw task_config_window.wgtw
	teaching_window.wgtw wndFileLocation.wgtw wndForceControl.wgtw
	wndTrajectoryReproduce.wgtw wnd_choose_option.wgtw
	wnd_conveyor_moves.wgtw wnd_conveyor_servo_algorithm.wgtw
	wnd_help_about.wgtw wnd_input_double.wgtw wnd_input_integer.wgtw
	wnd_irp6_mechatronika_inc.wgtw wnd_irp6_mechatronika_int.wgtw
	wnd_irp6_mechatronika_kinematic.wgtw
	wnd_irp6_mechatronika_servo_algorithm.wgtw
	wnd_irp6_mechatronika_xyz_angle_axis.wgtw
	wnd_irp6_mechatronika_xyz_angle_axis_ts.wgtw
	wnd_irp6_mechatronika_xyz_euler_zyz.wgtw
	wnd_irp6_mechatronika_xyz_euler_zyz_ts.wgtw wnd_irp6_on_track_inc.wgtw
	wnd_irp6_on_track_int.wgtw wnd_irp6_on_track_kinematic.wgtw
	wnd_irp6_on_track_servo_algorithm.wgtw
	wnd_irp6_on_track_xyz_angle_axis.wgtw
	wnd_irp6_on_track_xyz_angle_axis_relative.wgtw
	wnd_irp6_on_track_xyz_angle_axis_ts.wgtw
	wnd_irp6_on_track_xyz_euler_zyz.wgtw
	wnd_irp6_on_track_xyz_euler_zyz_ts.wgtw wnd_irp6_postument_inc.wgtw
	wnd_irp6_postument_int.wgtw wnd_irp6_postument_kinematic.wgtw
	wnd_irp6_postument_servo_algorithm.wgtw
	wnd_irp6_postument_xyz_angle_axis.wgtw
	wnd_irp6_postument_xyz_angle_axis_relative.wgtw
	wnd_irp6_postument_xyz_angle_axis_ts.wgtw
	wnd_irp6_postument_xyz_euler_zyz.wgtw
	wnd_irp6_postument_xyz_euler_zyz_ts.wgtw wnd_irp6ot_tfg_moves.wgtw
	wnd_irp6ot_tfg_servo_algorithm.wgtw wnd_irp6p_tfg_moves.wgtw
	wnd_irp6p_tfg_servo_algorithm.wgtw wnd_message.wgtw
	wnd_processes_control.wgtw wnd_speaker_play.wgtw yes_no_window.wgtw)

ADD_CUSTOM_COMMAND(
	OUTPUT ui.stage3
	COMMAND cmake -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/../../wgt ${CMAKE_CURRENT_BINARY_DIR}/../../wgt
	COMMAND $ENV{QNX_HOST}/usr/bin/phabbind ui ${ABMOD} 
	COMMAND cmake -E touch ui.stage3
	DEPENDS ui.stage2
)

ADD_CUSTOM_TARGET(ui_photon_application ALL DEPENDS ui.stage3)

install(TARGETS ui DESTINATION bin)