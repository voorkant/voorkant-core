#pragma once
#include "UIComponents.hpp"
#include <src/core/lv_event.h>
#include <src/draw/lv_img_buf.h>

class UIApexCard : public UIEntity
{
public:
  UIApexCard(HABackend &_backend, const std::string _panel, int _index, lv_obj_t* _parent);

  void uiupdate() override;

private:
  // FIXME: we never free() the lv_obj_t*'s in code
  lv_obj_t* chart;
  lv_obj_t* flowpanel;
  lv_chart_series_t* ser1;

  nlohmann::json data;

  static void drawEventCB(lv_event_t* _e);
};

/* definition of the card i'm currently trying to imitate

```yaml
type: custom:apexcharts-card
graph_span: 48h
span:
  start: day
now:
  show: true
  label: Nu
header:
  show: true
  title: Energieprijs per uur (€/kwh)
series:
  - entity: sensor.current_electricity_price_all_in
    show:
      legend_value: false
    stroke_width: 2
    float_precision: 3
    type: column
    opacity: 0.3
    color: '#03b2cb'
    data_generator: |
      return entity.attributes.prices.map((record, index) => {
        return [record.from, record.price];
      });
```

*/