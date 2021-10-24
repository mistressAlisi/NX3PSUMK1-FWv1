$(function () {
    $('#starttime').datetimepicker({
    format: 'LT',
    minDate: moment("00:00:00", "HH:mm:ss", true)
    
    });
    $('#endtime').datetimepicker({
    format: 'LT',
    maxDate: moment("23:59:59", "HH:mm:ss", true)
    });

    $("#starttime").on("dp.change", function (e) {
    $('#endtime').datetimepicker('minDate', e.date);
    });
    
    $("#endtime").on("dp.change", function (e) {
    $('#starttime').datetimepicker('maxDate', e.date);
    });

    window.sEdit = new _spectrumEdit();
    window.sEdit._initGraph();
});

