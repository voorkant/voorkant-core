#pragma once
#include "UIComponents.hpp"

class UIApexCard : public UIEntity
{
public:
  UIApexCard(json _card, lv_obj_t* _parent);

  void update() override;

private:
  // FIXME: we never free() the lv_obj_t*'s in code
  // lv_obj_t* chart_and_y_axis;
  lv_obj_t* chart;
  lv_obj_t* flowpanel;
  lv_obj_t* scale_y;
  lv_obj_t* scale_x;
  std::vector<std::string> labels_x;
  std::vector<const char*> labels_x_charp;
  lv_chart_series_t* ser1;

  std::vector<std::pair<time_t, double>> values; // return [record.from, record.price];

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