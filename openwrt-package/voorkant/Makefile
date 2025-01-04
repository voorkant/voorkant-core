# FIXME: license text here

include $(TOPDIR)/rules.mk

PKG_NAME:=voorkant
PKG_RELEASE:=0_git

PKG_LICENSE:=MIT

PKG_BUILD_DEPENDS:=curl nlohmannjson

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/meson.mk

define Package/voorkant
  SECTION:=utils
  CATEGORY:=Utilities
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

# FIXME: we should not need most, maybe all, of these
TARGET_LDFLAGS += -latomic -static -lstdc++ -lgcc_eh

$(eval $(call BuildPackage,voorkant))
