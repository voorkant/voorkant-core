# FIXME: license text here

include $(TOPDIR)/rules.mk

PKG_NAME:=voorkant
PKG_RELEASE:=0_git

PKG_LICENSE:=MIT

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/meson.mk

define Package/voorkant
  SECTION:=utils
  CATEGORY:=Utilities
  DEPENDS:=+libcurl +nlohmannjson +libatomic +libstdcpp
  TITLE:=Non-web Home Assistant frontend
endef

define Package/voorkant/description
  FIXME
endef

define Package/voorkant/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/openwrt-build/voorkant-lvgl $(1)/usr/bin/
endef

MESON_ARGS += \
	--prefer-static -Dlvgl-driver=fbdev -Dfront-ftxui=disabled

TARGET_LDFLAGS += -latomic

$(eval $(call BuildPackage,voorkant))
