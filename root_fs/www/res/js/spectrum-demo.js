
var $myPayloadMeter, $myFuelMeter;
		$( function () {
			// No need to declare DynaMeter vars outside this anonymous function, 
			// because the value-update code's also inside here.

			// Initialize payload meter and slider.
		    $myPayloadMeter = $("div#payloadMeterDiv").dynameter({
		    	width: 200,
		    	label: 'Output',
		    	value: 10,
		    	min: 0,
		    	max: 100,
		    	unit: '%',
		    	regions: {
		    		70: 'warn',
		    		90: 'error'
		    	}
		    });
		    $('div#payloadSliderDiv').slider({
		    	min: 0,
		    	max: 100,
		    	value: 10,
		    	step: 1,
                animate: true,
                
		    	slide: function (evt, ui) {
                    $.get("/api/spectrum_v1/set.json?v="+ui.value);
		    		$myPayloadMeter.changeValue(ui.value);
                    $
		    	}
		    });

		  
		});
$.get("/api/spectrum_v1/get.json",function(data) {
    $myPayloadMeter.changeValue(data.set);
     $('div#payloadSliderDiv').slider('value',data.set);
    
});
