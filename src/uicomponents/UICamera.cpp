#include "UICamera.hpp"
#include "logger.hpp"
#include <src/widgets/lv_img.h>

// FIXME: we do a whole lot of json parsing in this file, that we should be doing somewhere else.

UICamera::UICamera(std::shared_ptr<HAEntity> _entity, lv_obj_t* _parent) :
  UIEntity(_entity, _parent)
{
  auto state = entity->getJsonState();
  std::cerr << "INITIAL STATE FOR " << _entity->name << ":" << state.dump(2) << std::endl;

  if (!state.contains("attributes")) {
    throw std::runtime_error("Camera can't operate with a state that has no attributes");
  }

  auto attributes = state["attributes"];

  // We generate a UI based on 'supported_color_modes'. color_mode then tells us which mode to use. Color_mode should be in update()
  imgpanel = lv_img_create(_parent);
  lv_img_set_src(imgpanel, "A:test.png");
  // lv_obj_align(imgpanel, LV_ALIGN_LEFT_MID, 20, 0);

  update();
}

// code from https://curl.se/libcurl/c/getinmemory.html, modified

// FIXME: use std::array?
struct MemoryStruct {
  char *memory;
  size_t size;
};

static size_t
writeMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  char *ptr = static_cast<char*>(realloc(mem->memory, mem->size + realsize + 1));
  if(!ptr) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

// end code from

void UICamera::update()
{
  auto state = entity->getJsonState();
  std::cerr << "UPDATED STATE FOR " << entity->name << ":" << state.dump(2) << std::endl;

  {
    std::unique_lock<std::mutex> lvlock(g_lvgl_updatelock);
    auto url = "http://grace.7bits.nl:8123" + state["attributes"]["entity_picture"].get<string>();
    g_log << "camera URL: " << url << std::endl;

// code from as above, modified
    CURL *curl_handle;
    CURLcode res;

    struct MemoryStruct chunk;
    chunk.memory = static_cast<char*>(malloc(1));  /* grown as needed by the realloc above */
    chunk.size = 0;    /* no data at this point */

    curl_global_init(CURL_GLOBAL_ALL);

    /* init the curl session */
    curl_handle = curl_easy_init();

    /* specify URL to get */
    curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());

    /* send all data to this function  */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, writeMemoryCallback);

    /* we pass our 'chunk' struct to the callback function */
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);

    /* some servers do not like requests that are made without a user-agent
       field, so we provide one */
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");

    /* get it! */
    res = curl_easy_perform(curl_handle);

    /* check for errors */
    if(res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    }
    else {
      /*
       * Now, our chunk.memory points to a memory block that is chunk.size
       * bytes big and contains the remote file.
       *
       * Do something nice with it!
       */

      printf("%lu bytes retrieved\n", (unsigned long)chunk.size);
    }

    /* cleanup curl stuff */
    curl_easy_cleanup(curl_handle);
// end code from

    img = {
      .header = {
        .cf = LV_IMG_CF_RAW_ALPHA,
        .always_zero = 0,
        .w = 0,
        .h = 0,
      },
    };

    img.data_size = chunk.size;
    img.data = (uint8_t*)(chunk.memory);

    lv_img_set_src(imgpanel, &img);

    // free(chunk.memory); // FIXME this leaks terribly
  }
}
